#include "proportional_line_following.h"
#include "colour_sensing.h"

// Define the pins for the IR sensors. - Keith's Line following code 
// A0 green channel 1
// A1 yellow channel 2
// A2 orange channel 3
const int irPins[3] = {A0, A1, A2};

// Define values for the IR Sensor readings. - Keith's Line following code
int irSensorDigital[3] = {0, 0, 0};

// IR sensor threshold value for line detection. - Keith's Line following code
// 500 for vinyl sheets, 
// 800 for GRID LAB floor, 
// 700 for kitchen floor, 
int threshold = 700;

// binary representation of the sensor reading: 1 when the sensor detects the line, 0 otherwise. - Keith's Line following code 
int irSensors = B000;

// Binary representation of the last recorded sensor reading. - Reece
int lastIrReading;

void setupMotors() {  
  // Initialize the stepper driver control pins to output drive mode. - Keith's Line following code
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);

  // Start with drivers off, motors coasting. - Keith's Line following code
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);
}

/*
 * This method makes both the left and right tracks move forward at a specified speed. - Reece
 */
void moveForward(int pwmSpeed) {
  // Left motor,
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, HIGH);
  analogWrite(EN1_PIN, pwmSpeed);
  // Right motor, 
  digitalWrite(MOT_B1_PIN, HIGH);
  digitalWrite(MOT_B2_PIN, LOW);
  analogWrite(EN2_PIN, pwmSpeed);
}

/*
 * This method reverses the left tracks so that the robot moves to the left at a specified speed. - Reece
 */
void turnLeft(int pwmSpeed) {
  // Left motor,
  digitalWrite(MOT_A1_PIN, HIGH);
  digitalWrite(MOT_A2_PIN, LOW);
  analogWrite(EN1_PIN, pwmSpeed);
  // Right motor, 
  digitalWrite(MOT_B1_PIN, HIGH);
  digitalWrite(MOT_B2_PIN, LOW);
  analogWrite(EN2_PIN, pwmSpeed);
}

/*
 * This method reverses the right tracks so that the robot moves to the right at a specified speed. - Reece
 */
void turnRight(int pwmSpeed) {
  // Left motor,
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, HIGH);
  analogWrite(EN1_PIN, pwmSpeed);
  // Right motor, 
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, HIGH);
  analogWrite(EN2_PIN, pwmSpeed);
}

void stop() {
  // Left motor,
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  analogWrite(EN1_PIN, 0);
  // Right motor, 
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);
  analogWrite(EN2_PIN, 0);
}

/*
 * This method reads all the IR sensors and converts them into a binary representation of all 3 readings. - Keith's Line following code
 */
void scan() {
  // Initialize the sensors
  irSensors = B000;

  for (int i = 0; i < 3; i++) {
    int sensorValue = analogRead(irPins[i]);
    if (sensorValue >= threshold) {
      irSensorDigital[i] = 1;
    }

    else {
      irSensorDigital[i] = 0;
    }

    int b = 2 - i;
    irSensors = irSensors + (irSensorDigital[i] << b);
  }
}

/*
 * This method reads the binary sensor reading and depending on the values within it, 
 * updates the direction the motors are turning for a specified period of time. - Reece
 */
void updateDirection(int duration, String state) {
  
  if (state.equals("inTransit")) {
    switch (irSensors) {

    case B000:// Not on the line,
          
      // If the last recorded reading indicated that the line was on the left: turn left, 
      if (lastIrReading == B110 || lastIrReading == B100) {
        turnLeft(220);
        
      // If the last recorded reading indicated that the line was on the right: turn right,  
      } else if (lastIrReading == B011 || lastIrReading == B001) {
        turnRight(220);
      }
      break;

    case B100:// Line is very left, 
      turnLeft(255);
      break;

    case B110:// Line is kinda left, 
      turnLeft(255);
      break;

    case B010:// On the line, 
      // If the line is red: 
      moveForward(255);
      break;

    case B011:// Line is kinda right,
      turnRight(255);
      break;

    case B001:// Line is very right,
      turnRight(255);
      break;

    case B111:// Perpendicular to the line, 
      turnRight(220);
      break;
    }
  }

  // If the current reading indicates that the line is present: replace the last recorded reading with the current reading,
  if (irSensors != B000) {
    lastIrReading = irSensors;
  }

  delay(duration);
}
