/*
    Declerations for RFID_Handler
*/
#ifndef RFID_HANDLER_H
#define RFID_HANDLER_H

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 3

extern Servo myservo;
extern MFRC522 mfrc522;
extern bool authorised;

void rfid_setup();
bool check_user();
//void RFID_handler();


#endif