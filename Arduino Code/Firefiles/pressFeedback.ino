//Single-click feedback
void pressFeedback() {
  for (byte i = 40; i > 0; i = i - 2) {
    pixels.setBrightness(i);
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(3);
  }
  pixels.setBrightness(0);
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(10);
}

//Double-click feedback
void doublepressFeedback() {
  oneLed(0x000000, 0);
  pixels.show();
  delay(120);
  oneLed(colorArray[*ColorIndexPointer], 0);
  pixels.show();
  delay(120);
  oneLed(0x000000, 0);
  pixels.show();
  delay(120);
}

void configEntered() {

  // Lock signal color to [singalColor]
  Serial.println("**Entered Configuration Mode!**");
  oneLed(signalColor, 0);
  pixels.show();
}

void settingsSaved() {

  // Feedbak when the network credential is saved
  Serial.println("**Network Setting Saved!**");
  oneLed(savedColor, 0);
  pixels.show();
}
