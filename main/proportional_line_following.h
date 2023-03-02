#pragma once

#include <Arduino.h>

// Define the motor pins. - Reece
#define MOT_A1_PIN 5
#define MOT_A2_PIN 6
#define EN1_PIN 3

#define MOT_B1_PIN 9
#define MOT_B2_PIN 10
#define EN2_PIN 11

void setupMotors();
void moveForward(int pwmSpeed);
void turnRight(int pwmSpeed);
void turnLeft(int pwmSpeed);
void stop();
void scan();
void updateDirection(int duration, String state);
