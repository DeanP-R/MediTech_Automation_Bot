#include "HardwareSerial.h"
// Include the colour sensing header file
#include "colour_sensing.h"

// Create an object of the Adafruit_TCS34725 class for the colour sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/**
  \brief
    This function configures the TCA9548A multiplexer to use channel 4, 
    initializes the colour sensor with the I2C address 0x29, 
    and sets the pins to drive an LED. On ESP32 boards, 
    the LEDC interface is used to control the pins, while on other boards, 
    the pin modes are set to OUTPUT.
  \param
    None.
  \return
    None.
*/
void setupColourSensor() {
  // Configure the TCA9548A multiplexer to use the fourth channel
  TCA9548A(3);
  // Initialize the colour sensor with the I2C address 0x29
  if (!tcs.begin(0x29)) {
    tcs.disable();
    tcs.enable();
    Serial.println("Trying");
    delay(500);
  }

  TCA9548A(3);
  // Initialize the colour sensor with the I2C address 0x29
  while (!tcs.begin(0x29)) {
    tcs.disable();
    tcs.enable();
    Serial.println("Trying");
    delay(500);
  }
}

/**
  \brief
    This function reads the RGB values from the colour sensor, 
    stores them in the RGB array, and prints them to the serial port. 
     It selects channel 4 on the TCA9548A multiplexer, turns on the LED, disables the colour sensor interrupt, 
    and reads the RGB values from the colour sensor. Then, it turns off the LED, enables the colour sensor interrupt, 
    converts the RGB values to integers, and stores them in the RGB array.
  \param
    None.
  \return
    None.
*/
void readColourSensor(int* RGB) {
  float red, green, blue;
  // Select channel 4 on the TCA9548A multiplexer
  TCA9548A(3);
  // Turn on the LED and disable the colour sensor interrupt
  tcs.setInterrupt(false);
  // Read the RGB values from the colour sensor
  tcs.getRGB(&red, &green, &blue);
  // Turn off the LED and enable the colour sensor interrupt
  tcs.setInterrupt(true);
  // Convert the RGB values to integers and store them in the RGB array
  RGB[0] = int(red);
  RGB[1] = int(green);
  RGB[2] = int(blue); 

  // Print the RGB values to the serial port
  Serial.println("Red Value: " + String(RGB[0]) + " Green Value: " + String(RGB[1]) + " Blue Value: " + String(RGB[2]));
}
