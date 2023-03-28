#include "HardwareSerial.h"
// Include the colour sensing header file
#include "colour_sensing.h"

// Create an object of the Adafruit_TCS34725 class for the colour sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
// Create an array to store the RGB values read from the colour sensor
int RGB[3];

/*
 * This method starts the colour sensor,
 * Assigns and initializes the pins used for the colour sensor,
 * and sets up the pins used to control an LED. 
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
  if (!tcs.begin(0x29)) {
    tcs.disable();
    tcs.enable();
    Serial.println("Trying");
    delay(500);
  }
}

/*
 * This method reads the RGB values from the colour sensor,
 * and stores them in the RGB array.
 */
void readColourSensor() {
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
  Serial.print("Red Value: " + String(RGB[0]) + " Green Value: " + String(RGB[1]) + " Blue Value: " + String(RGB[2]) + " ---|--- ");
}

void detectColour(String targetWard, String state, bool medicineDelivered) {
  
  readColourSensor();

  if (RGB[0] > 140) {
    if (targetWard == "home") {
      stop();
      state = "stopped";

    } else if (targetWard = "red") {
      targetWard = "home";
      stop();
      delay(1000);
      turnRight(255);
      delay(625);      
    }
        
  } else if (RGB[2] > 100) {
    if (targetWard == "home") {
      stop();
      state = "stopped";

    } else if (targetWard == "blue") {
      targetWard = "home";
      stop();
      delay(1000);
      turnRight(255);
      delay(625);
    }
  
  } 
  else if (RGB[0] > 100 && RGB[2] < 50) {
    if (targetWard == "home") {
      stop();
      state = "stopped";

    } else if (targetWard == "yellow") {
      targetWard = "home";
      stop();
      delay(1000);
      turnRight(255);
      delay(625);
    }
  
  } else {
    state = "inTransit";

  }
}
