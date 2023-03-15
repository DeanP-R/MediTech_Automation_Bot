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
    // Set the pin modes for the sensor shutdown
    pinMode(SHT_LEFT, OUTPUT);
    pinMode(SHT_CENTER, OUTPUT);
    pinMode(SHT_RIGHT, OUTPUT);

    // Turn off all the sensors
    digitalWrite(SHT_LEFT, LOW);
    digitalWrite(SHT_CENTER, LOW);
    digitalWrite(SHT_RIGHT, LOW);
  
    // Delay for 10ms
    delay(10);
  
    // Turn on all the sensors
    digitalWrite(SHT_LEFT, HIGH);
    digitalWrite(SHT_CENTER, HIGH);
    digitalWrite(SHT_RIGHT, HIGH);
    delay(10);

    // Activate the left sensor and reset the center and right sensors
    digitalWrite(SHT_LEFT, HIGH);
    digitalWrite(SHT_CENTER, LOW);
    digitalWrite(SHT_RIGHT, LOW);

    // Initialize the left sensor
    if (!leftLaser.begin(LEFT_ADDRESS)) {
        while (1);
    }
    delay(10);

    // Activate the center sensor
    digitalWrite(SHT_CENTER, HIGH);
    delay(10);

    // Initialize the center sensor
    if (!centerLaser.begin(CENTER_ADDRESS)) {
        while (1);
    }

    // Activate the right sensor
    digitalWrite(SHT_RIGHT, HIGH);
    delay(10);

    // Initialize the right sensor
    if (!rightLaser.begin(RIGHT_ADDRESS)) {
        while (1);
    }
}

// Method to read the laser sensors and save the data into an array
void readLaserSensors() {
    // Read the left sensor and save the data into leftValue
    leftLaser.rangingTest(&leftValue, false);
    // Read the center sensor and save the data into centerValue
    centerLaser.rangingTest(&centerValue, false);
    // Read the right sensor and save the data into rightValue
    rightLaser.rangingTest(&rightValue, false);

    // Convert the range data into millimeters and save each sensor's distance value into the corresponding index of the passed array
    LCR[0] = leftValue.RangeMilliMeter;
    LCR[1] = centerValue.RangeMilliMeter;
    LCR[2] = rightValue.RangeMilliMeter;
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

void avoidance(){
  //Update TOF sensor values
  readLaserSensors();
  //Consideration distance - distance at which Fred will perform evasive maneuver
  if(LCR[0] < 200 || LCR[1] < 200 || LCR[2] < 200){
    //Calculate differnce between left and right sensors
    int leftToRightSensor = LCR[0] - LCR[2];
    //If difference is +ve - obstacle is on the right - turn to left
    if(leftToRightSensor > 0){
      swerveLeft();
    }
    else if(leftToRightSensor < 0){
      //If difference is -ve - obstacle is on the left - turn right
      swerveRight();
    }
    else{
      //If there is no difference, re-run calculation
      avoidance();
    }
  }
}