/****************************************************************************************
  File Name       : MediTech Automation Control                                         *
  Version         : 0.1.0                                                               *
  Description     : Main code for B39VS - System Project                                *
  Author          : Dean Rowlett & Reece Alexander                                      *
  Target          : Arduino Uno Revision 3                                              *
  Compiler        : avr-g++                                                             *
  IDE             : Arduino 2.0.3                                                       *
  Programmer      : Arduino ISP (In-System Programmer)                                  *
  Last Updated    : 27th January 2023                                                   *
****************************************************************************************/
#include "RFID_handler.h"

Servo myservo;
bool authorised = false;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  rfid_setup();

}

void loop() {
  check_user();

}


/*
Realistically we'll probs have 2 motors, 4-6 ultrasonic sensors, 1 line following module, 1 colour module, 1 latch, 1 keypad, 1 rfid module, 1-2 lcd screens, weight sensor 
or another ultrasonic sensor to tell the robot when to go. Can't think of much else atm but ill ask at the meeting and see what they're saying 
*/
