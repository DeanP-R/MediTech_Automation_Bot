// Include the h file, 
#include "colour_sensing.h"

// Create a colour sensor object. - Example colorview code
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/*
 * This method starts the colour sensor,
 * Assigns and initialises the colour sensor pins, 
 * Then creates a gamma table to convert the RGB data into observable human colours. - Example colorview code
 */
void setupColourSensor() {
  tcs.begin(0x29);
  
  // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif
}

/*
 * This method reads the colour sensor, 
 * Then populates a provided array with RGB values for the rest of the program to use. - Example colorview code
 */
void readColourSensor(int* RGB) {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED

  RGB[0] = int(red);
  RGB[1] = int(green);
  RGB[2] = int(blue); 
}
