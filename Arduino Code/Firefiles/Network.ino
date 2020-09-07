void onDemandAP() {
  //if double click, enters demandAP configuration
  byte demandTrigger = 0;
  demandTrigger = checkButton();
  //if single click, update colorQueue to the remote device
  if (demandTrigger == 1) {
    Serial.println("Single Click!");
  }

  if (demandTrigger == 2) {
    Serial.println("Double Click!");
    //reset settings - for testing
    WiFiManager wifiManager;
    wifiManager.resetSettings();
  }
  Serial.print(".");
  delay(50);
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
