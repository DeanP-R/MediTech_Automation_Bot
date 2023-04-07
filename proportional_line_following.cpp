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
// 700 for GRID LAB floor, 
// 700 for kitchen floor, 
int threshold = 700;

// binary representation of the sensor reading: 1 when the sensor detects the line, 0 otherwise. - Keith's Line following code 
int irSensors = B000;

// Binary representation of the last recorded sensor reading. - Reece
int lastIrReading;

/**
  \brief
    This function initializes the pins used to control the stepper motor driver to output mode, 
    and sets their initial states to LOW, which results in the motors coasting.
  \param
    None.
  \return
    None.
*/
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

/**
  \brief
    This function moves the robot forward by setting the control pins for the left and right motors. 
    The left motor rotates clockwise, while the right motor rotates counterclockwise, 
    resulting in forward motion. The speed of both motors is controlled by the pwmSpeed parameter.
  \param
    pwmSpeed: 
      An integer value between 0 and 255 that sets the speed of both motors.
  \return
    None.
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

void antiForward(int pwmSpeed) {
  // Left motor,
  digitalWrite(MOT_A1_PIN, HIGH);
  digitalWrite(MOT_A2_PIN, LOW);
  analogWrite(EN1_PIN, pwmSpeed);
  // Right motor, 
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, HIGH);
  analogWrite(EN2_PIN, pwmSpeed);
}

/**
  \brief
    This function turns the robot left by setting the control pins for the left and right motors. 
    The left motor rotates counterclockwise, while the right motor rotates counterclockwise, 
    resulting in a left turn. The speed of both motors is controlled by the pwmSpeed parameter.
  \param
      An integer value between 0 and 255 that sets the speed of both motors.
  \return
    None.
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

/**
  \brief
    This function turns the robot right by setting the control pins for the left and right motors. 
    The left motor rotates clockwise, while the right motor rotates counterclockwise, 
    resulting in a right turn. The speed of both motors is controlled by the pwmSpeed parameter.    
  \param
      An integer value between 0 and 255 that sets the speed of both motors.
  \return
    None.
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
/**
  \brief
    This function stops the robot by setting the control pins for the left and right motors to LOW, 
    and the PWM output to 0, which stops the motors.
  \param
    None.
  \return
    None.
*/
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

/**
  \brief
    This function scans the IR sensors and converts the analog sensor readings to digital values based on a threshold value. 
    The digital sensor values are then combined to form a single byte representing the sensor readings.
  \param
    None.
  \return
    None.
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

  // Serial.print("L: ");
  // Serial.print(analogRead(irPins[0]));
  // Serial.print(" C: ");
  // Serial.print(analogRead(irPins[1]));
  // Serial.print(" R: ");
  // Serial.println(analogRead(irPins[2]));
}

/**
  \brief
    This function updates the direction of movement based on the current state of the IR sensors. 
    If the state is "inTransit", the function checks the current sensor readings and turns left or right 
    based on the last recorded sensor reading. The function also updates the last recorded sensor reading 
    if the current reading indicates that the line is present.
  \param
    duration: an integer representing the duration of the movement in milliseconds
  \return
    None.
*/
void updateDirection(int duration) {
  
  switch (irSensors) {

  case B000:// Not on the line,
        
    // If the last recorded reading indicated that the line was on the left: turn left, 
    if (lastIrReading == B110 || lastIrReading == B100) {
      moveForward(200);
      
    // If the last recorded reading indicated that the line was on the right: turn right,  
    } else if (lastIrReading == B011 || lastIrReading == B001) {
      moveForward(200);
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
    moveForward(200);
    break;

  case B011:// Line is kinda right,
    turnRight(255);
    break;

  case B001:// Line is very right,
    turnRight(255);
    break;

  case B111:// Perpendicular to the line, 
    turnRight(255);
    break;
  }

  // If the current reading indicates that the line is present: replace the last recorded reading with the current reading,
  if (irSensors != B000) {
    lastIrReading = irSensors;
  }

  delay(duration);
}
