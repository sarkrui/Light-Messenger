void WPAPersonalInit() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WPAPersonal Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
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
