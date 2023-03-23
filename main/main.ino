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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int bus = 0;  // default channel on the multiplexer

LiquidCrystal_I2C lcd1(0x27, 20, 4);
Adafruit_VL53L0X laser = Adafruit_VL53L0X();
String state = "inTransit";

void setup() {
  Serial.begin(9600);
  // setupLasers();
  //setupMotors();
  //setupColourSensor();
  //lockSetup();
  Serial.println("setup complete these nuts ya bam");
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
}

void loop() {
  //avoidance();
  // moveForward(255);
  // scan();
  // updateDirection(2, state);
  //lock_op();
  // readLaserSensors();
  //readColourSensor();
  //runSpeaker();
  digitalWrite(22, HIGH);
  delay(500);
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  delay(500);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  delay(500);
  digitalWrite(24, LOW);

}
/*

*/
