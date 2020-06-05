# Light Messenger
As we might live apart with our closed friends due to some reality resons which could be studying aboard, business travel, so on. To compensate for the missed contact with a certain relationship, I created Light Messenger, an IoT kit for a couple of friends having bi-directional communication with colors. With it, you can 1) select light different colors by rotation; 2) send your current selected light color by a single-tap; 3) or review the light color(s) the other sends by a double-tap.



### Demo
[![IMAGE ALT TEXT HERE](https://i.loli.net/2020/06/05/7GHx2AzFbREiuD9.jpg)](https://video.pxing.design/Videos/Light-Messenger_Demo.m4v)



### Config

```c++
#define FIREBASE_HOST "xxxxxxxx.firebaseio.com" //Realtime database host without https:// 
#define FIREBASE_AUTH ""    //Projects/Settings/Service accounts/Database secrets
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_CODE"

#define DEVICE_ID 1 //YOUR_ID
//#define DEVICE_ID 2 ///YOUR_COUPLE_ID                  

#if (DEVICE_ID == 1)
const String device_id = "/YOUR_NAME";
const String remote_device_id = "/YOUR_COUPLE_NAME";
#endif

#if (DEVICE_ID == 2)
const String device_id = "/YOUR_COUPLE_NAME";
const String remote_device_id = "/YOUR_NAME";
#endif
```



### Dependencies

| Name | Version |
| ---- | ---- |
|Adafruit_NeoPixel.h| 1.3.3 |
|FirebaseESP8266.h| 2.7.9 |
|ESP8266WiFi.h| 2.6.3 |
|Arduino.h| 1.8.10 SDK |
|FirebaseJson.h| 2.2.9 |
|SimpleRotary.h| 1.1.2 |



### Credit

This is a give away for a left professor, Saskia Bakker from the TU Eindhoven. Although I redesigned completely the software layer, the physical form was heavily built upon her Ph.D. prototope, **Fireflies**. Besides, you could find my Wizard of Oz for the [initial demo](https://pxing.design/demo-on-saskias-farewell/) on her Goodbye party; I would like give **@mobizt** credit for developing the [Firebase Realtime Database library for ESP8266](https://github.com/mobizt/Firebase-ESP8266) as well as his time in fixing bugs. 

