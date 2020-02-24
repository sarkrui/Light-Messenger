//This function will be called when a single-click is made
void updateRemoteQueue() {
  //Delare a FirebaseJsonData for storing
  FirebaseJsonData remoteJsonData;
  //Fetch JSON from Firebase
  Serial.println("Get JSON");
  Firebase.get(firebaseData, "/fireflies");

  //created json object
  //store firebaseData.jsonObject() in as the value of remoteJson
  FirebaseJson &remoteJson = firebaseData.jsonObject();
  remoteJsonData = firebaseData.jsonData();

  //parse /<remote_device_id>/tapped
  remoteJson.get(remoteJsonData, remote_device_id + "/tapped");
  boolean remoteTapped = remoteJsonData.boolValue;
  Serial.println("Remote Tappped:");
  Serial.println(remoteTapped);

  //parse /<remote_device_id>/tapped
  remoteJson.get(remoteJsonData, device_id + "/tapped");
  boolean localTapped = remoteJsonData.boolValue;
  Serial.println("Local Tapped:");
  Serial.println(localTapped);

  //if remoteTapped being pushed
  //empty (remote) colorQueue and
  //add current colorIndex to remote colorQueue at index:0

  if (remoteTapped == true) {
    Serial.println("Tapped");
    //empty queue and set from index:0
    remoteJson.remove(remote_device_id + "/colorQueue");
    remoteJson.set(remote_device_id + "/colorQueue/[0]", ColorIndex);
    remoteJson.set(remote_device_id + "/tapped", false);

    //if a new colorQueue has been set on the remote device
    //set "tapped" state on remote to false
    remoteJson.set(device_id + "/tapped", false);
  }
  //if remoteTapped not being pushed
  //then append current (local) colorindex to remote colorQueue
  else if (remoteTapped == false) {
    Serial.println("Not Tapped");
    //append colorIndex to colorQueue
    Serial.println(remote_device_id);
    //Declare a firebasejsonArray for the remote device
    FirebaseJsonArray queueArr;
    remoteJson.get(remoteJsonData, remote_device_id + "/colorQueue");
    remoteJsonData.getArray(queueArr);
    Serial.println(queueArr.size());
    remoteJson.set(remote_device_id + "/colorQueue/[" + String(queueArr.size()) + "]", ColorIndex);
  }
  //remoteJson.set(remote_device_id + "/tapped", false);
  String jsonStr;
  remoteJson.toString(jsonStr, true);
  Serial.println(jsonStr);

  //Push updated colorQueue
  Firebase.updateNode(firebaseData, "/fireflies", remoteJson);
  Serial.println("Push JSON");
}
