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
  lockSetup(); 
  // setupMotors();
  // setupLasers();
  // setupColourSensor();  
  lock_op(targetWard);  
  // Serial.begin(9600);
  // lockSetup(); 
  setupMotors();
  // setupLasers();
  setupColourSensor();  
  // targetWard = lock_op();    #
  // Serial.println("setup");
}

/*
@ 255 625 == 
*/

void loop() {
  moveForward(200);
  scan();
  updateDirection(2, inTransit);

  // readColourSensor();
  // readLaserSensors();

  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  
  // avoidance();#
  // scan();
  // updateDirection(2, state);
  // Serial.println("loop");
  
  // detectColour(targetWard, inTransit);  
  readColourSensor(RGB);

  if (RGB[0] > 140) {
    if (targetWard == "home") {
      stop();
      inTransit = false;

    } else if (targetWard == "red") {
      stop();
      delay(1000);
      turnRight(255);
      delay(625);  
      targetWard = "home";    
    }
        
  } else if (RGB[2] > 100) {
    if (targetWard == "home") {
      stop();
      inTransit = false;

    } else if (targetWard == "blue") {
      stop();
      delay(1000);
      turnRight(255);
      delay(625);
      targetWard = "home";
    }
  
  } else if (RGB[0] > 100 && RGB[2] < 50) {
    if (targetWard == "home") {
      stop();
      inTransit = false;

    } else if (targetWard == "yellow") {
      stop();
      delay(1000);
      turnRight(255);
      delay(625);
      targetWard = "home";
    }
  
  } else {
    inTransit = true;
    moveForward(200);

  }
  
}
