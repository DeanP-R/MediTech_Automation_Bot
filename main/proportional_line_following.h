#pragma once

#include <Arduino.h>

// Define the motor pins. - Reece
#define MOT_A1_PIN 25 //blue
#define MOT_A2_PIN 26 //green 
#define EN1_PIN 10    //green

#define MOT_B1_PIN 27 //purple
#define MOT_B2_PIN 28 //yellow
#define EN2_PIN 9     //blue

void setupMotors();
void moveForward(int pwmSpeed);
void turnRight(int pwmSpeed);
void turnLeft(int pwmSpeed);
void stop();
void scan();
void updateDirection(int duration, bool inTransit);
