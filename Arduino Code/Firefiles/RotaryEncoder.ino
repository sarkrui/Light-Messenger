
//RotaryEncoder Function combines: rotary.rotate() + checkButton()
//4-Way Button: Click, Double-Click, Press+Hold, and Press+Long-Hold Test Sketch By Jeff Saltzman
//https://github.com/mprograms/SimpleRotary
//https://forum.arduino.cc/index.php?topic=14479.0

void RotaryEncoder() {

  byte x, y; //defines variables for rotation and push
  x = rotary.rotate();
  y = checkButton();

  if (x == 1) {
    RotateCount++;
    *RotaryPositionPointer += 8;
  }
  else if (x == 2) {
    RotateCount--;
    *RotaryPositionPointer -= 8;
  }

  //if single click, update colorQueue to the remote device
  if (y == 1) {
    *ColorIndexPointer = map(*RotaryPositionPointer, 0, 255, 0, 10);
    pressFeedback();
    Serial.println("Single Click!");
    updateRemoteQueue();
  }

  //if double click, slowly replay remote queue
  if (y == 2) {
    doublepressFeedback();
    readLocalColorQueue();
    Serial.println("Double Click!");
    dispMode = 1;
  }

  //if double click, empty local queue
  if (y == 3 || y == 4) {
    *ColorIndexPointer = map(RotaryPosition, 0, 255, 0, 10);
    Serial.println("Long Press");
    oneLed(0x000000, 0);
    pixels.show();
    delay(500);
    emptyLocalQueue();
  }
  *ColorIndexPointer = map(RotaryPosition, 0, 255, 0, 10);
}
