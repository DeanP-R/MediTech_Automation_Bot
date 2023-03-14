#include "object_avoidance.h"

// Create each laser sensor object, 
Adafruit_VL53L0X leftLaser = Adafruit_VL53L0X();
Adafruit_VL53L0X centerLaser = Adafruit_VL53L0X();
Adafruit_VL53L0X rightLaser = Adafruit_VL53L0X();

// Address we will assign if triple sensor is present,
#define LEFT_ADDRESS 0x30
#define CENTER_ADDRESS 0x31
#define RIGHT_ADDRESS 0x32

// Set the pins to shutdown,
#define SHT_LEFT 38
#define SHT_CENTER 39
#define SHT_RIGHT 40

// Create a variable to store each sensors range data
VL53L0X_RangingMeasurementData_t leftValue;
VL53L0X_RangingMeasurementData_t centerValue;
VL53L0X_RangingMeasurementData_t rightValue;


void setupLasers() {
    // Need to find addresses, 
    pinMode(SHT_LEFT, OUTPUT);
    pinMode(SHT_CENTER, OUTPUT);
    pinMode(SHT_RIGHT, OUTPUT);

    // All reset,
    digitalWrite(SHT_LEFT, LOW);
    digitalWrite(SHT_CENTER, LOW);
    digitalWrite(SHT_RIGHT, LOW);
  
    delay(10);
  
    // All unreset,
    digitalWrite(SHT_LEFT, HIGH);
    digitalWrite(SHT_CENTER, HIGH);
    digitalWrite(SHT_RIGHT, HIGH);
    delay(10);

    // Activating LOX1 and reseting LOX2 & LOX3,
    digitalWrite(SHT_LEFT, HIGH);
    digitalWrite(SHT_CENTER, LOW);
    digitalWrite(SHT_RIGHT, LOW);

    // Initing LOX1,
    if (!leftLaser.begin(LEFT_ADDRESS)) {
      while (1);
    }
    delay(10);

    // Activating LOX2,
    digitalWrite(SHT_CENTER, HIGH);
    delay(10);

    // Initing LOX2,
    if (!centerLaser.begin(CENTER_ADDRESS)) {
      while (1);
    }

    // Activating LOX3,
    digitalWrite(SHT_RIGHT, HIGH);
    delay(10);

    // Initing LOX3,
    if (!rightLaser.begin(RIGHT_ADDRESS)) {
      while (1);
    }
}

void readLaserSensors(int* LCR) {
    // Checks to see if I2C address was set succesfully - if so saves the sensor data into the passed variable, 
    leftLaser.rangingTest(&leftValue, false);
    centerLaser.rangingTest(&centerValue, false);
    rightLaser.rangingTest(&rightValue, false);

    // Converts the sensor data into millimeters and saves each sensors distance value into their corresponding index. - Reece
    LCR[0] = leftValue.RangeMilliMeter;
    LCR[1] = centerValue.RangeMilliMeter;
    LCR[2] = rightValue.RangeMilliMeter;
}

void swerveRight() {
    turnRight(255);
    delay(625);

    stop();
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
