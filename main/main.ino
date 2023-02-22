/****************************************************************************************
  File Name       : MediTech Automation Control                                         *
  Version         : 0.1.5                                                               *
  Description     : Main code for B39VS - System Project                                *
  Author          : Dean Rowlett & Reece Alexander                                      *
  Target          : Arduino Uno Revision 3                                              *
  Compiler        : avr-g++                                                             *
  IDE             : Arduino 2.0.3                                                       *
  Programmer      : Arduino ISP (In-System Programmer)                                  *
  Last Updated    : 22nd February 2023                                                  *
****************************************************************************************/
#include "RFID_handler.h"
#include "track_movement.h"
#include "proportional_line_following.h"
void setup() {
  setupMotors();

}

void loop() {
  moveForward(200);
  scan();
  updateDirection(2);
}
