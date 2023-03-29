/****************************************************************************************
  File Name       : MediTech Automation Control                                         *
  Version         : 0.3.1                                                               *
  Description     : Main code for B39VS - System Project                                *
  Author          : Dean Rowlett & Reece Alexander                                      *
  Target          : Arduino Mega                                                        *
  Compiler        : avr-g++                                                             *
  IDE             : Arduino 2.0.3                                                       *
  Programmer      : Arduino ISP (In-System Programmer)                                  *
  Last Updated    : 28th March 2023                                                     *
****************************************************************************************/

//test these nuts ya bam

#include "speakers.h"
#include "proportional_line_following.h"
#include "colour_sensing.h"
#include "object_avoidance.h"
#include "lock.h"
#include "multiplexer.h"

int bus = 0;  // default channel on the multiplexer

bool inTransit = true;

String targetWard = "home";

// Create an array to store the RGB values read from the colour sensor
int RGB[3];

void setup() {
  Serial.begin(9600);

  pinMode(24, OUTPUT);// rED
  pinMode(22, OUTPUT);// green
  pinMode(23, OUTPUT);// yellow
  
  // lockSetup(); 
  // setupMotors();
  setupLasers();
//   setupColourSensor();  
//   targetWard = lock_op();    
}

/*
@ 255 625 == 
*/

void loop() {
  
  readLaserSensors();
  
  // avoidance(); 

  // digitalWrite(24, HIGH);
  // digitalWrite(22, LOW);
  // digitalWrite(23, LOW);

  // readColourSensor(RGB);

  // if (RGB[0] > 140) {     //red
  //   stop();
  //   inTransit = false;
  //   targetWard = lock_op();
  //   turnRight(255);
  //   delay(200);
  //   moveForward(180);
  //   delay(200);
        
  // } else if (RGB[2] > 100 && targetWard == "blue") {  //blue
  //   stop();
  //   delay(1000);
  //   turnRight(255);
  //   delay(312);
  
  // } else if (RGB[0] > 100 && RGB[2] < 50) { //yellow
  //   stop();
  //   delay(1000);
  //   turnRight(255);
  //   delay(200);
  
  // } else {
  //   inTransit = true;
  //   moveForward(180);

  // }

  // scan();
  // updateDirection(2, inTransit); 
}
