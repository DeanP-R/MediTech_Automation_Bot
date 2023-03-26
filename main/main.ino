/****************************************************************************************
  File Name       : MediTech Automation Control                                         *
  Version         : 0.3.1                                                               *
  Description     : Main code for B39VS - System Project                                *
  Author          : Dean Rowlett & Reece Alexander                                      *
  Target          : Arduino Mega                                                        *
  Compiler        : avr-g++                                                             *
  IDE             : Arduino 2.0.3                                                       *
  Programmer      : Arduino ISP (In-System Programmer)                                  *
  Last Updated    : 23th March 2023                                                     *
****************************************************************************************/

//test these nuts ya bam

#include "speakers.h"
#include "proportional_line_following.h"
#include "colour_sensing.h"
#include "object_avoidance.h"
#include "lock.h"
#include "multiplexer.h"
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

int bus = 0;  // default channel on the multiplexer

// LiquidCrystal_I2C lcd1(0x27, 20, 4);
// Adafruit_VL53L0X laser = Adafruit_VL53L0X();
String state = "inTransit";

String targetWard = "Home";

void setup() {
  Serial.begin(9600);
  lockSetup(); 
  // setupMotors();
  // setupLasers();
  // setupColourSensor();
  // Serial.println("setup complete these nuts ya bam");
}

void loop() {
  // avoidance();
  // readLaserSensors();
  // readColourSensor();
  // runSpeaker();
  lock_op(targetWard);

  // Possible final loop() layout ------------------
  
  // avoidance();
  
  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  
  // detectColour();  

  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  
  // -----------------------------------------------

}
/*

*/
