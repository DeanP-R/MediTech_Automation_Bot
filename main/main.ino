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

String targetWard = "home";

// Create an array to store the RGB values read from the colour sensor
int RGB[3];

void setup() {
  Serial.begin(9600);

  pinMode(24, OUTPUT);// rED
  pinMode(22, OUTPUT);// green
  pinMode(23, OUTPUT);// yellow
  
  lockSetup(); 
  setupMotors();
  setupLasers();
  setupColourSensor();  
  targetWard = lock_op();    
}

/*
@ pwm 255: 
1250 delay = 180 degree turn
625 delay = 90 degree turn
313 delay = 45 degree turn
*/

void loop() {
  
  // // Task 1
  // digitalWrite(24, HIGH);
  // digitalWrite(22, LOW);
  // digitalWrite(23, LOW);

  // // Task 2
  // readLeftSensor();
  // moveForward(200);
  // scan();
  // updateDirection(2);

  // // Task 3
  // readCenterSensor();
  // moveForward(200);
  // scan();
  // updateDirection(2);
  
  // // Task 4
  // readRightSensor();
  // moveForward(200);
  // scan();
  // updateDirection(2);
  
  // // Task 5
  // avoidance(); 
  // moveForward(200);
  // scan();
  // updateDirection(2);

  // Task 6
  readColourSensor(RGB);

  // while (RGB[0] > 140) {     //red
  //   moveForward(200);
  //   delay(100);
  //   stop();
  //   targetWard = lock_op();
  //   readColourSensor(RGB);    
  // }
  
  // if (RGB[2] > 100 && targetWard == "blue") {  //blue
  //   stop();
  //   delay(1000);
  //   turnRight(255);
  //   delay(312);
  
  // } else if (RGB[0] > 100 && RGB[2] < 50 && targetWard == "yellow") { //yellow
  //   stop();
  //   delay(1000);
  //   turnRight(255);
  //   delay(200);
  
  // }
  // moveForward(200);
  // scan();
  // updateDirection(2); 
}
