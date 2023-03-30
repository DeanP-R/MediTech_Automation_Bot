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

int consDist = 200;

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

  // Read the center sensor and save the data into centerValue
  TCA9548A(1);
  centerLaser.rangingTest(&centerValue, false);
  LCR[1] = centerValue.RangeMilliMeter;

  // Read the right sensor and save the data into rightValue
  TCA9548A(2);
  rightLaser.rangingTest(&rightValue, false);
  LCR[2] = rightValue.RangeMilliMeter;

  // Serial.println("Left Reading: " + String(LCR[0]) + " | Center Reading: " + String(LCR[1]) + " | Right Reading: " + String(LCR[2]));
}

void readLeftSensor() {
  // Read the left sensor and save the data into leftValue
  TCA9548A(0);
  leftLaser.rangingTest(&leftValue, false);
  LCR[0] = leftValue.RangeMilliMeter;
}

void readCenterSensor() {
  // Read the center sensor and save the data into centerValue
  TCA9548A(1);
  centerLaser.rangingTest(&centerValue, false);
  LCR[1] = centerValue.RangeMilliMeter;
}

void readRightSensor() {
  // Read the right sensor and save the data into rightValue
  TCA9548A(2);
  rightLaser.rangingTest(&rightValue, false);
  LCR[2] = rightValue.RangeMilliMeter;
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

  // moveForward(200);
  // delay(1000);
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

  // moveForward(200);
  // delay(1000);
}

void avoidance() {

  //Consideration distance - distance at which Fred will perform evasive maneuver
  if (LCR[0] < consDist || LCR[1] < consDist || LCR[2] < consDist) {
    
    digitalWrite(24, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, HIGH);
    
    stop();

    for (int a = 1; a <= 5; a++) {
      digitalWrite(24, LOW);
      digitalWrite(22, LOW);
      digitalWrite(23, LOW);
       
      delay(500);

      digitalWrite(24, LOW);
      digitalWrite(22, LOW);
      digitalWrite(23, HIGH);

      delay(500);
    }
    readLaserSensors();  
    //Consideration distance - distance at which Fred will perform evasive maneuver
    while (LCR[0] < consDist || LCR[1] < consDist || LCR[2] < consDist) {
      // Calculate differnce between left and right sensors
      int leftToRightSensor = LCR[0] - LCR[2];
      
      //If difference is +ve - obstacle is on the right - turn to left
      if (leftToRightSensor > 0) {
        // Serial.println("Swerve Left");
        swerveLeft();

      //If difference is -ve - obstacle is on the left - turn right  
      } else if (leftToRightSensor < 0) {
        // Serial.println("Swerve right");
        swerveRight();
      
      //If there is no difference, re-run calculation      
      } else {
        // Serial.println("Deciding");
        avoidance();
        
      }

      readLaserSensors();      
    }
  }
}