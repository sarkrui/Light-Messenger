//-------------------------/dispMode
//------------------------------/0: dimmed light mode(color defined by users)
//------------------------------/1: Playing Message Mode ()

void displayShow() {

  //Playing Message Mode
  if (dispMode == 1) {

    //temp variables for breathing timing
    byte minLight = 5;
    byte maxLight = 90;
    byte interval = 25;

    for (byte i = 0; i < actualQueueSize && actualQueueSize != 0 && blinkColorQueue[i] != 404; i++) {
      for (byte j = minLight; j <= maxLight; j++) {
        oneLed(colorArray[blinkColorQueue[i]], 0); //set all Leds color
        pixels.setBrightness(j);
        pixels.show();
        delay(interval);
      }
      oneLed(colorArray[blinkColorQueue[i]], 0); //set all Leds color
      pixels.setBrightness(maxLight);
      delay(3000);
      for (byte j = maxLight; j >= minLight ; j--) {
        oneLed(colorArray[blinkColorQueue[i]], 0); //set all Leds color
        pixels.setBrightness(j);
        pixels.show();
        delay(interval);
      }
    }

    //empty local queue when
    //the local queue has been played once
    emptyLocalQueue();
    //set dispMode back to Idle mode
    dispMode = 0;
  }

  //Idle Mode
  else {
    RotaryEncoder();
    oneLed(colorArray[*ColorIndexPointer], 0); //set all Leds color
    pixels.setBrightness(40); //set brightness
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(15);
  }
}
