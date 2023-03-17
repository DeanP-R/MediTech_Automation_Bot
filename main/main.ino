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
#include "multiplexer.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Create an array for colour sensor values. - Reece
int RGB[3];
int bus = 0;  // default channel on the multiplexer

LiquidCrystal_I2C lcd1(0x27, 20, 4);
Adafruit_VL53L0X laser = Adafruit_VL53L0X();
String state = "inTransit";

void setup() {
  Serial.begin(9600);
  //setupLasers();
  //Serial1.begin(9600);
  //setupMotors(); 
  // setupLaserTest(laser, 38, 1);
  // setupLaserTest(laser, 39, 2);
  // setupLaserTest(laser, 40, 3);
  //setupColourSensor();
  //lockSetup();
  // lcd1.init();
  // lcd1.backlight(); 
}

void loop() {
  // avoidance();
  // moveForward(255);
  // scan();
  // updateDirection(2, state);
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
  Serial.println("enter loop");
  readLaserSensors();
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
    // select the desired channel on the multiplexer
  // TCA9548A(channel);

  // // print to the LCD screen
  // lcd.setCursor(0, 0);  // set the cursor to the first position on the first line
  // lcd.print("bAlLz!");  // print the message

  // delay(1000);  // wait for a second before updating the display
  // lcd1.setCursor(0,0);
  // lcd1.print("BAllz"); 
}

/*

*/