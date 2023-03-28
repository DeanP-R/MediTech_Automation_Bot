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
  pinMode(SHT_LEFT, OUTPUT);
  pinMode(SHT_CENTER, OUTPUT);
  pinMode(SHT_RIGHT, OUTPUT);

  digitalWrite(SHT_LEFT, LOW);
  digitalWrite(SHT_CENTER, LOW);
  digitalWrite(SHT_RIGHT, LOW);

  digitalWrite(SHT_LEFT, HIGH);
  TCA9548A(0);
  if (!leftLaser.begin(LEFT_ADDRESS)) {
    Serial.println("Trying left.");
    digitalWrite(SHT_LEFT, LOW);
    delay(10);
    digitalWrite(SHT_LEFT, HIGH);
  }
  delay(10);

  digitalWrite(SHT_CENTER, HIGH);
  TCA9548A(1);
  while (!centerLaser.begin(CENTER_ADDRESS)) {
    Serial.println("Trying center.");
    digitalWrite(SHT_CENTER, LOW);
    delay(10);
    digitalWrite(SHT_CENTER, HIGH);
  }
  delay(10);

  digitalWrite(SHT_RIGHT, HIGH);
  TCA9548A(2);
  while (!rightLaser.begin(RIGHT_ADDRESS)) {
    Serial.println("Trying right.");
    digitalWrite(SHT_RIGHT, LOW);
    delay(10);
    digitalWrite(SHT_RIGHT, HIGH);
  }
  delay(10);

  digitalWrite(SHT_LEFT, HIGH);
  TCA9548A(0);
  while (!leftLaser.begin(LEFT_ADDRESS)) {
    Serial.println("Trying left.");
    digitalWrite(SHT_LEFT, LOW);
    delay(10);
    digitalWrite(SHT_LEFT, HIGH);
  }
  delay(10);  
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
      // Serial.println("Swerve Left");
      swerveLeft();
    } else if (leftToRightSensor < 0) {
      //If difference is -ve - obstacle is on the left - turn right
      // Serial.println("Swerve right");
      swerveRight();
    } else {
      //If there is no difference, re-run calculation
      // Serial.println("Deciding");
      avoidance();
    }
  }
}