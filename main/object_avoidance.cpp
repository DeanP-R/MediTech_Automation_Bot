#include "Arduino.h"
// Import the necessary libraries
#include "object_avoidance.h"

// Create an object for each laser sensor (left, center, right)
Adafruit_VL53L0X leftLaser = Adafruit_VL53L0X();
Adafruit_VL53L0X centerLaser = Adafruit_VL53L0X();
Adafruit_VL53L0X rightLaser = Adafruit_VL53L0X();

// Set the I2C addresses for the laser sensors
#define LEFT_ADDRESS 0x30
#define CENTER_ADDRESS 0x31
#define RIGHT_ADDRESS 0x32


// Set the pins for the laser sensor shutdown
#define SHT_LEFT 38
#define SHT_CENTER 39
#define SHT_RIGHT 40

//create integer array for storing TOF sensor values
int LCR[3];

// Create variables to store the range data for each sensor
VL53L0X_RangingMeasurementData_t leftValue;
VL53L0X_RangingMeasurementData_t centerValue;
VL53L0X_RangingMeasurementData_t rightValue;




// Method to initialize the laser sensors
void setupLasers() {  
  // Initialize the laser sensors
  delay(400);
 
  TCA9548A(0);
  leftLaser.begin(LEFT_ADDRESS);
  delay(400);

  TCA9548A(1);
  centerLaser.begin(CENTER_ADDRESS);
  delay(400);

  TCA9548A(2);
  rightLaser.begin(RIGHT_ADDRESS);
  delay(400);
}
// Method to read the laser sensors and save the data into an array

void readLaserSensors() {
  // Read the left sensor and save the data into leftValue
  TCA9548A(0);
  leftLaser.rangingTest(&leftValue, false);
  LCR[0] = leftValue.RangeMilliMeter;
  // Serial.print("Left Reading: ");
  // Serial.print(LCR[0]);

  // Read the center sensor and save the data into centerValue
  TCA9548A(1);
  centerLaser.rangingTest(&centerValue, false);
  LCR[1] = centerValue.RangeMilliMeter;
  // Serial.print(" | Center Reading: ");
  // Serial.print(LCR[1]);

  // Read the right sensor and save the data into rightValue
  TCA9548A(2);
  rightLaser.rangingTest(&rightValue, false);
  LCR[2] = rightValue.RangeMilliMeter;
  // Serial.print(" | Right Reading: ");
  // Serial.println(LCR[2]);

  // Print the sensor values, if necessary
  // Serial.print("Left Value: ");
  // Serial.print(LCR[0]);
  // Serial.print(" | Center value: ");
  // Serial.print(LCR[1]);
  // Serial.print(" | Right Value:" );
  // Serial.println(LCR[2]);
}

//------------------------

// Method to swerve right to avoid an object
void swerveRight() {
  // Turn the robot right at maximum speed
  turnRight(255);
  // Delay for 625ms
  delay(625);

  // Stop the robot
  stop();
  // Delay for 1 second
  delay(1000);

  moveForward(200);
  delay(1000);

  stop();
  delay(1000);

  turnLeft(255);
  delay(700);

  stop();
  delay(1000);

  moveForward(200);
  delay(1000);
}

void swerveLeft() {
  turnLeft(255);
  delay(625);

  stop();
  delay(1000);

  moveForward(200);
  delay(1000);

  stop();
  delay(1000);

  turnRight(255);
  delay(700);

  stop();
  delay(1000);

  moveForward(200);
  delay(1000);
}

void avoidance() {
  
  //Update TOF sensor values
  readLaserSensors();
  //Consideration distance - distance at which Fred will perform evasive maneuver
  if (LCR[0] < 200 || LCR[1] < 200 || LCR[2] < 200) {
    //Calculate differnce between left and right sensors
    int leftToRightSensor = LCR[0] - LCR[2];
    //If difference is +ve - obstacle is on the right - turn to left
    if (leftToRightSensor > 0) {
      swerveLeft();
    } else if (leftToRightSensor < 0) {
      //If difference is -ve - obstacle is on the left - turn right
      swerveRight();
    } else {
      //If there is no difference, re-run calculation
      avoidance();
    }
  }
}