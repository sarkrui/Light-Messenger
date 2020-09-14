# Light Messenger
As we might live apart with our closed friends due to some reality resons which could be studying aboard, business travel, so on. To compensate for the missed contact with a certain relationship, I created Light Messenger, an IoT kit for a couple of friends having bi-directional communication with different light colors. With this kit, you can 1) select light different colors by rotation; 2) send your current selected light color by a single-tap; 3) or review the light color(s) the other sends by a double-tap.



### Use Demo

[![IMAGE ALT TEXT HERE](https://i.loli.net/2020/06/05/7GHx2AzFbREiuD9.jpg)](https://vimeo.com/421278858)



### Configuration Demo

[![IMAGE ALT TEXT HERE](https://i.imgur.com/Pujw7Ju.jpg)](https://vimeo.com/455801532)



### Config in Sketch

```c++
#define FIREBASE_HOST "xxxxxxxx.firebaseio.com" //Realtime database host without https:// 
#define FIREBASE_AUTH ""    //Projects/Settings/Service accounts/Database secrets
#define SoftAP_SSID "ANY_NAME_YOU_PREFER"

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

### Config after compile

1. Powering up the `Light-Messenger`
2. While it's blinking in `Red`, double-click to enter the Network configuration mode
3. Using wireless terminal to connect to SSID `Light-Messenger-AP`
4. Configurating the Wi-Fi settings according to your context
5. Once the `Light-Messenger` turns Green, it's connected to Internet!



### Erase Flash (Optional)

In some cases, you might want to erase all contents of ESP8266 (including Wi-Fi settings, Sketch). You can try using `esptool.py` with below command line:

List all connected serial devices

```bash
ls /dev/tty.wchusbserial*
```

Print your nodemcu `port-id`

```bash
$/dev/tty.wchusbserial14540
```

Execute esptool.py -p [device_id] erase_flash

```bash
esptool.py -p /dev/tty.wchusbserial14540 erase_flash
```

If you have only one serial device connected, you could 

```bash
esptool.py -p /dev/tty.wchusbserial* erase_flash
```



### Dependencies

| Name | Version |
| ---- | ---- |
|Adafruit_NeoPixel.h| 1.3.3 |
|FirebaseESP8266.h| 2.7.9 |
|ESP8266WiFi.h| 2.6.3 |
|Arduino.h| 1.8.13 SDK |
|FirebaseJson.h| 2.2.9 |
|SimpleRotary.h| 1.1.2 |
|[WiFIManager](https://github.com/tzapu/WiFiManager) by [tzapu](https://github.com/tzapu)| 0.15.0 |



### To-do

- [x] Incorporate [AutoConnect](https://github.com/Hieromon/AutoConnect) for WLAN configuration at run time
- [x] Adding instrction for connecting to Wi-Fi and restoring credentials
- [ ] Add [companion UI apps](https://github.com/mobizt/ESPForm) for credential management for `Firebase RTDB`
- [ ] Add pre-compiled firmware for flashing
- [ ] Add manual for setting up `Firebase RTDB` for the Project exclusively 
- [ ] Construct an OOCSI-based version for better latency in Europe
- [ ] Build 3D printed model to replace the laser cut base



### Credit

This is a give away for a resigned professor, Saskia Bakker from the TU Eindhoven. In this project, I redesigned completely the software layer, the physical form was heavily built upon Saskia's Ph.D. prototope, **Fireflies**. Thanks for that! Besides, you could find my Wizard of Oz for the [initial demo](https://pxing.design/demo-on-saskias-farewell/) on her Goodbye party; I would also like give **@mobizt** credit for developing the [Firebase Realtime Database library for ESP8266](https://github.com/mobizt/Firebase-ESP8266) as well as his time in fixing bugs. 



## MIT License

Copyright (c) 2020 P. XING (Sark)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 