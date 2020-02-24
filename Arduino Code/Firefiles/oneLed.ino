//This function aims to simplify codes, using Hex code to set the led strip color
//ledNum 0: all
//ledNum [1 - NUMPIXELS]
void oneLed(unsigned long colorHex, int ledNum) {

  char R = colorHex >> 16; // right bit shift 16 bits
  char G = colorHex >> 8 & 0xFF; //right bit shift 8 bits
  char B = colorHex & 0xFF;


  if (ledNum == 0) {
    for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(R, G, B)); // Moderately bright green color.
    }
  }
  else {
    pixels.clear();
    for (int j = 0; j < ledNum; j++) {
      pixels.setPixelColor(j, pixels.Color(R, G, B)); // Moderately bright green color.
    }
  }
}
