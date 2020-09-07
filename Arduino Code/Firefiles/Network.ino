// Light Indicator for reset
void bootSignal(bool state) {

  switch (state) {
    case true:
      oneLed(0x000000, 0);
      pixels.show();
      break;

    case false:
      oneLed(0x220000, 0);
      pixels.show();
      break;

    default:

      break;
  }
}

//if double click, enters WiFiManagerReset Program
void wifiManagerReset() {

  byte demandTrigger = 0;
  demandTrigger = checkButton();
  delay(50);
  if (demandTrigger == 2) {
    Serial.println("Double Click!");
    //reset settings - for testing
    WiFiManager wifiManager;
    wifiManager.resetSettings();
  }
  // Hold  seconds for trigger detection
  if (millis() - signalMillis >= 200) {
    //Serial.print(".");
    bootSignal(signalState);
    signalState = !signalState;
    signalMillis = millis();
  }
}

void autoAP() {
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  wifiManager.setMinimumSignalQuality(20);

  //tries to connect to last known settings
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP" with password "password"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect(SoftAP_SSID)) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
}

void checkNetwork() {

  currentMillis = millis();
  if (currentMillis - startMillis >= timeBetweenSamples) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connection failed...");
      Serial.println("Rebooting...");
      ESP.restart();
    }
    startMillis = currentMillis;
  }

}


void dataSetup() {

  setupJSON.setJsonData("{\"tue\":{\"tapped\":false,\"colorQueue\":[]},\"philips\":{\"tapped\":false,\"colorQueue\":[]}}");
  if (Firebase.setJSON(firebaseData, root, setupJSON)) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
  }
  else {
    Serial.println("ERROR: " + firebaseData.errorReason());
  }
}
