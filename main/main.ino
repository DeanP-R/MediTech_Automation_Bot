/****************************************************************************************
  File Name       : MediTech Automation Control                                         *
  Version         : 0.3.0                                                               *
  Description     : Main code for B39VS - System Project                                *
  Author          : Dean Rowlett & Reece Alexander                                      *
  Target          : Arduino Mega                                                        *
  Compiler        : avr-g++                                                             *
  IDE             : Arduino 2.0.3                                                       *
  Programmer      : Arduino ISP (In-System Programmer)                                  *
  Last Updated    : 15th March 2023                                                     *
****************************************************************************************/
#include "proportional_line_following.h"
#include "colour_sensing.h"
#include "object_avoidance.h"
#include "lock.h"

// Create an array for colour sensor values. - Reece
int RGB[3];

String state = "inTransit";

void setup() {
  // Serial.begin(9600);
  //Serial1.begin(9600);
  setupMotors(); 
  setupLasers();
  //setupColourSensor();
  //lockSetup();
}

void loop() {
  avoidance();
  moveForward(255);
  scan();
  updateDirection(2, state);
  //lock_op();
  // readColourSensor(RGB); 
  // Serial.print("Colour Sensor: ");
  // Serial.print("R: ");
  // Serial.print(RGB[0]);
  // Serial.print(" G: ");
  // Serial.print(RGB[1]);
  // Serial.print(" B: ");
  // Serial.print(RGB[2]);
  // Serial.print(", ");

  // readLaserSensors(LCR);
  // Serial.print("Lasers: ");
  // Serial.print("L: ");
  // Serial.print(LCR[0]);
  // Serial.print(" C: ");
  // Serial.print(LCR[1]);
  // Serial.print(" R: ");
  // Serial.print(LCR[2]);
  // Serial.println(" ");

  // while(Serial1.available()>0){
  //   //char uno_data = Serial1.read();
  //   Serial.println(Serial1.read());

  // if (RGB[0] > 140) {
  //   stop();
  //   state = "stopped";

  // } else if (RGB[2] > 100) {
  //   turnLeft(255); 
  //   delay(1250);
  //   moveForward(200);
  // } else if (LCR[1] <= 150) {
  //   if (LCR[0] < LCR[2] || LCR[0] <= 150) {
  //     swerveRight();
  //   } else if (LCR[2] < LCR[0] || LCR[2] <= 150) {
  //     swerveLeft();
  //   }

  // } else {
  // state = "inTransit";
  // }
}

/*

*/