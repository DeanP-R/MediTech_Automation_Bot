#include "track_movement.h"
#include <Arduino.h>

/*
  Additional functions for motor control and movement.
  <>setup_Motor_Control:
        write description here
  <>reverse:
        write description here
  <>turn_Right:
        write description here
  <>turn_left:
        write description here
*/

#define NUM_SENSORS 3
#define Kp 1.0
#define Ki 1.0
#define Kd 1.0

int sensors[NUM_SENSORS];
int sensor_reading;
int error;
int prev_error = 0;
int integral = 0;
int derivative;
int control_signal;

void setup_Motor_Control() {
  // Initialize the stepper driver control pins as outputs
  pinMode(LEFT_TRACK_1_PIN, OUTPUT);
  pinMode(LEFT_TRACK_2_PIN, OUTPUT);
  pinMode(RIGHT_TRACK_1_PIN, OUTPUT);
  pinMode(RIGHT_TRACK_2_PIN, OUTPUT);
  pinMode(ENABLE_A, OUTPUT);
  pinMode(ENABLE_B, OUTPUT);

  // Initialize the sensor pins as inputs
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensors[i], INPUT);
  }
}

void forward() {
  // Read the values from the sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor_reading += analogRead(sensors[i]);
  }
  sensor_reading /= NUM_SENSORS;

  // Calculate the error between the sensor reading and the target value
  error = sensor_reading - 512;

  // Calculate the integral and derivative terms
  integral += error;
  derivative = error - prev_error;

  // Calculate the control signal using the PID formula
  control_signal = Kp * error + Ki * integral + Kd * derivative;

  // Adjust the speed of the motors based on the control signal
  int left_speed = constrain(MOTOR_SPEED + control_signal, 0, 255);
  int right_speed = constrain(MOTOR_SPEED - control_signal, 0, 255);

  // Left track forward
  digitalWrite(LEFT_TRACK_1_PIN, LOW);
  digitalWrite(LEFT_TRACK_2_PIN, HIGH);

  // Right track forward
  digitalWrite(RIGHT_TRACK_1_PIN, HIGH);
  digitalWrite(RIGHT_TRACK_2_PIN, LOW);

  // Assign speeds
  analogWrite(ENABLE_A, left_speed);
  analogWrite(ENABLE_B, right_speed);

  // Store the error for the next iteration
  prev_error = error;
}

// The rest of the functions remain the same.

void reverse() {
  // Left track backward
  digitalWrite(LEFT_TRACK_1_PIN, HIGH);
  digitalWrite(LEFT_TRACK_2_PIN, LOW);

  // Right track backward
  digitalWrite(RIGHT_TRACK_1_PIN, LOW);
  digitalWrite(RIGHT_TRACK_2_PIN, HIGH);

  // Assign speeds
  analogWrite(ENABLE_A, MOTOR_SPEED);
  analogWrite(ENABLE_B, MOTOR_SPEED);
}

void turn_Right() {
  // Left track forward
  digitalWrite(LEFT_TRACK_1_PIN, HIGH);
  digitalWrite(LEFT_TRACK_2_PIN, LOW);

  // Right track backward
  digitalWrite(RIGHT_TRACK_1_PIN, HIGH);
  digitalWrite(RIGHT_TRACK_2_PIN, LOW);

  // Assign speeds
  analogWrite(ENABLE_A, MOTOR_SPEED);
  analogWrite(ENABLE_B, MOTOR_SPEED);
}
void turn_Left() {
  // Left track forward
  digitalWrite(LEFT_TRACK_1_PIN, HIGH);
  digitalWrite(LEFT_TRACK_2_PIN, LOW);

  // Right track backward
  digitalWrite(RIGHT_TRACK_1_PIN, HIGH);
  digitalWrite(RIGHT_TRACK_2_PIN, LOW);

  // Assign speeds
  analogWrite(ENABLE_A, MOTOR_SPEED);
  analogWrite(ENABLE_B, MOTOR_SPEED);
}
