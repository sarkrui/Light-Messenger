# Light Messenger
Light Messenger is an IoT kit for a couple of friends having bi-directional communication with colors. It allows you to 

* Select light different color by rotation; 

* Send your current selected light color by single-tap;
* Play the light color(s) you received by double-tap;



### Config

```c++
#define FIREBASE_HOST "xxxxxxxx.firebaseio.com" //Realtime database host without https:// 
#define FIREBASE_AUTH ""    //Projects/Settings/Service accounts/Database secrets
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_CODE"

#define DEVICE_ID 1 
//#define DEVICE_ID 2                  

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

