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

String state = "inTransit";

bool medicineDelivered = false;

String targetWard = "home";

void setup() {
  Serial.begin(9600);
  lockSetup(); 
  // setupMotors();
  // setupLasers();
  // setupColourSensor();  
  lock_op(targetWard);  
}

void loop() {

  // readColourSensor();
  // readLaserSensors();

  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  
  // avoidance();
  
  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  
  // detectColour(targetWard, state, medicineDelivered);  

  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  
}
