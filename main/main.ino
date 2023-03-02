/****************************************************************************************
  File Name       : MediTech Automation Control                                         *
  Version         : 0.1.5                                                               *
  Description     : Main code for B39VS - System Project                                *
  Author          : Dean Rowlett & Reece Alexander                                      *
  Target          : Arduino Uno Revision 3                                              *
  Compiler        : avr-g++                                                             *
  IDE             : Arduino 2.0.3                                                       *
  Programmer      : Arduino ISP (In-System Programmer)                                  *
  Last Updated    : 23nd February 2023                                                  *
****************************************************************************************/
#include "proportional_line_following.h"
#include "colour_sensing.h"

// Create an array for colour sensor values. - Reece
int RGB[3];

String state = "inTransit";

void setup() {
  // Serial.begin(9600);
  setupMotors();
  setupColourSensor(); 
}

void loop() {
  readColourSensor(RGB); 

  if (RGB[0] > 140) {
    stop();
    state = "stopped";

  } else if (RGB[2] > 100) {
    turnLeft(255);
    delay(1000);
    moveForward(200);

  } else {
    moveForward(200);
    state = "inTransit";
  }
  // Serial.print("R: ");
  // Serial.print(RGB[0]);
  // Serial.print(" G: ");
  // Serial.print(RGB[1]);
  // Serial.print(" B: ");
  // Serial.print(RGB[2]);
  // Serial.print(" ");
  // Serial.println(reading);
  
  scan();
  updateDirection(2, state);
}


