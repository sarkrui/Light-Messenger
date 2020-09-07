//-----------------------------------
//---------NeoPixel LED HERE---------
//-----------------------------------
#include <Adafruit_NeoPixel.h>
#define PIN            D3
#define NUMPIXELS      20
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
unsigned int dispMode = 0;
byte blinkColorQueue[256];//Array for blinking

//-------------Firebase --------------------
//--------Data structure--------------------
//--------/fireflies------------------------
//-------------/Philips (id:0)
//---------------------/dispMode
//------------------------------/0: Playing Message Mode
//------------------------------/1: Idle Mode
//---------------------/tapped
//------------------------------------------
//-------------/TU Eindhoven (id:1)
//-------------------------/dispMode
//------------------------------/0: Playing Message Mode
//------------------------------/1: Idle Mode
//---------------------/tapped
//------------------------------------------
//FirebaseESP8266.h must be included before ESP8266WiFi.h


#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <Arduino.h>
#include "FirebaseJson.h"

#define FIREBASE_HOST "xxxxxxx.firebaseio.com" //Realtime database host without https:// 
#define FIREBASE_AUTH ""    //Projects/Settings/Service accounts/Database secrets

#define DEVICE_ID 1                 //id: 1 for Person A
//#define DEVICE_ID 2               //id: 2 for Person B

#define SoftAP_SSID "Light-Messenger"

#if (DEVICE_ID == 1)
const String device_id = "/philips";
const String remote_device_id = "/tue";
const String soft_ssid = "Fireflies-Philips";
#endif

#if (DEVICE_ID == 2)
const String device_id = "/tue";
const String remote_device_id = "/philips";
const String soft_ssid = "Fireflies-TU/e";

#endif

String root = "/fireflies/";
String philips = "/fireflies/philips";
String tue = "/fireflies/tue";
String device_local_path;                //define device path for ESP to push to
String device_remote_path;               //define device path for ESP to pull from
FirebaseData firebaseData;               //Declare the Firebase Data object in global scope
FirebaseJson setupJSON;

//-----------------------------------
//---------HEX Colors ---------------
//-----------------------------------

unsigned long colorArray[] = {
  0x330000, 0xDD4500, 0xAA8000,
  0xDDDD00, 0x00DD30, 0x00DDDD,
  0xAAAA99, 0x000044, 0x5500DD,
  0x500050
};



//-----------------------------------
//---------Rotary Coder HERE---------
//-----------------------------------

#include <SimpleRotary.h>
#define buttonPin D7             // digital input pin
SimpleRotary rotary(D5, D6, D9); // Pin A, Pin B, Button Pin

byte i, j;
byte RotaryPosition = 127;
byte *RotaryPositionPointer = &RotaryPosition;
int ColorIndex = 0;
int *ColorIndexPointer = &ColorIndex;

// Button timing variables
int debounce = 50;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 500;            // max ms between clicks for a double click event
int holdTime = 2000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 5000;    // ms long hold period: how long to wait for press+hold event

// Button variables
boolean signalState = false;// variable for signalState during bootup
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

//-----------------------------------
//----Super Rainbow Detect HERE------
//-----------------------------------
int CWTimes = 0;
int CCWTimes = 0;
int PushTimes = 0;
int RotateCount = 0; //initialize RotateCount number for SuperRainbowDetect()

//-----------------------------------
//-----Queue Replay Detect HERE-----
//-----------------------------------
boolean tapped = false;
byte actualQueueSize = 0;    //Real actualQueueSize

//-----------------------------------
//-----Timer Variables --------------
//-----------------------------------
unsigned long startMillis = 0;
unsigned long currentMillis = 0;
unsigned long signalMillis = 0;
int timeBetweenSamples = 5000;

// put your setup code here, to run once:
void setup() {

  Serial.begin(115200);
  Serial.println("\n Starting");
  // Set button input pin
  pinMode(buttonPin, INPUT_PULLUP);

  // This initializes the NeoPixel library.
  pixels.begin();
  dispMode = 0;


  // Hold 5 seconds for trigger detection
  startMillis = millis();
  signalMillis = millis();
  while (millis() - startMillis <= 5000) {
    wifiManagerReset();
  }

  //If no wifiManagerReset() required, enters autoAP
  autoAP();
  //Output device ID
  Serial.println();
  Serial.print("This is device: ");
  Serial.print(device_id);
  Serial.print("\n");

  //Firebase connectivity
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "small");
}

void loop() {
  //Breathing mode or flashing mode
  displayShow();
  checkNetwork();
}
