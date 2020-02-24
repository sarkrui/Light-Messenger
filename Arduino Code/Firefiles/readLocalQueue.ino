//This function reads local queue from /localDeviceid
//and it is called when a double-click is made
void readLocalColorQueue() {
  //Fetch JSON from Firebase
  Firebase.get(firebaseData, "/fireflies");
  FirebaseJson &localJson = firebaseData.jsonObject();
  FirebaseJsonData localJsonData;
  localJsonData = firebaseData.jsonData();
  localJson.get(localJsonData, device_id + "/colorQueue");

  //  localJson.get(localJsonData, "/philips/colorQueue");
  FirebaseJsonArray queueArr2;
  localJsonData.getArray(queueArr2);

  //store localQueue array in blinkColorQueue[]
  actualQueueSize = queueArr2.size();

  for (size_t i = 0; i < (sizeof(blinkColorQueue) / sizeof(blinkColorQueue[0])); i++) {
    //Serialize with a 404 index;
    blinkColorQueue[i] = 404;
  }

  for (size_t i = 0; i < actualQueueSize; i++) {
    queueArr2.get(localJsonData, i);
    blinkColorQueue[i] = localJsonData.intValue;
  }
  //print out blinkColorQueue
  for (size_t i = 0; i < actualQueueSize; i++) {
    Serial.print(blinkColorQueue[i]);
    Serial.print(",");
  }

  //change local press state
  //needs to be uncommented if running with displayShow();
  localJson.set(device_id + "/tapped", true);

  String jsonStr;
  localJson.toString(jsonStr, true);
  Serial.println(jsonStr);

  //Push updated colorQueue
  Firebase.updateNode(firebaseData, "/fireflies", localJson);
  Serial.println("Push JSON");
}
