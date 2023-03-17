#include "Arduino.h"
// Import the necessary libraries
#include "object_avoidance.h"

// Create an object for each laser sensor (left, center, right)
Adafruit_VL53L0X leftLaser = Adafruit_VL53L0X();
Adafruit_VL53L0X centerLaser = Adafruit_VL53L0X();
Adafruit_VL53L0X rightLaser = Adafruit_VL53L0X();

// Set the I2C addresses for the laser sensors
#define LEFT_ADDRESS 0x29
#define CENTER_ADDRESS 0x2A
#define RIGHT_ADDRESS 0x2B


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
   // Initialize the left sensor ------------------------------------
  digitalWrite(SHT_LEFT, HIGH);
  delay(10);

  TCA9548A(0);
  if (!leftLaser.begin(LEFT_ADDRESS)) {
    Serial.println("Setup Error: Left Laser");
    while (1);
  }
  Serial.println("Left Laser Setup Success");
  delay(1000);

  // Activate the center sensor --------------------------------------
  digitalWrite(SHT_CENTER, HIGH);
  delay(10);

  TCA9548A(1);
  // Initialize the center sensor
  if (!centerLaser.begin(CENTER_ADDRESS)) {
    Serial.println("Setup Error: Center Laser");
    while (1);
  }
  Serial.println("Center Laser Setup Success");
  delay(1000);

  // Activate the right sensor ------------------------------
  digitalWrite(SHT_RIGHT, HIGH);
  delay(10);

  // Initialize the right sensor
  TCA9548A(2);
  if (!rightLaser.begin(RIGHT_ADDRESS)) {
    Serial.println("Setup Error: Right Laser");
    while (1);
  }
  Serial.println("Right Laser Setup Success");
  delay(1000);
}

// Method to read the laser sensors and save the data into an array
void readLaserSensors() {
  // Read the left sensor and save the data into leftValue
  //Serial.println("Selecting channel 0");
  TCA9548A(0);
  //Serial.println("Selected channel 0");
  if (leftLaser.begin(LEFT_ADDRESS)) {
    leftLaser.rangingTest(&leftValue, false);
    LCR[0] = leftValue.RangeMilliMeter;
    Serial.print("Left Value: ");
    Serial.print(LCR[0]);
  }

  // Read the center sensor and save the data into centerValue
  //Serial.println("Selecting channel 1");
  TCA9548A(1);
  //Serial.println("Selected channel 1");
  if (centerLaser.begin(RIGHT_ADDRESS)) {
    centerLaser.rangingTest(&centerValue, false);
    LCR[1] = centerValue.RangeMilliMeter;
    Serial.print(" | Center value: ");
    Serial.print(LCR[1]);
  }
  // Read the right sensor and save the data into rightValue
  //Serial.println("Selecting channel 2");
  TCA9548A(2);
  //Serial.println("Selected channel 2");
  if (rightLaser.begin(RIGHT_ADDRESS)) {
    rightLaser.rangingTest(&rightValue, false);
    LCR[2] = rightValue.RangeMilliMeter;
    Serial.print(" | Right Value:" );
    Serial.println(LCR[2]);
  }
  // Convert the range data into millimeters and save each sensor's distance value into the corresponding index of the passed array

  //readLaserSensors(LCR);
  // Serial.print("Lasers: ");
  // Serial.print("L: ");
  // Serial.print(LCR[0]);
  // Serial.print(" C: ");
  // Serial.print(LCR[1]);
  // Serial.print(" R: ");
  // Serial.print(LCR[2]);
  // Serial.println(" ");
}

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