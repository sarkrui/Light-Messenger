//Clear local queue
void emptyLocalQueue() {
  //Delare a FirebaseJsonData for storing
  FirebaseJsonData remoteJsonData;
  //Fetch JSON from Firebase
  //Serial.println("Get JSON");
  //Firebase.get(firebaseData, "/fireflies");
  //created json object
  //store firebaseData.jsonObject() in as the value of remoteJson
  FirebaseJson &remoteJson = firebaseData.jsonObject();

  //empty local device queue and mark tapped: true
  remoteJson.remove(device_id + "/colorQueue");
  remoteJson.set(device_id + "/tapped", true);

  String jsonStr;
  remoteJson.toString(jsonStr, true);
  Serial.println(jsonStr);

  //Push updated colorQueue
  Firebase.updateNode(firebaseData, "/fireflies", remoteJson);
  Serial.println("Push JSON");
}
