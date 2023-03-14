/*
  Declarations for speakers.cpp
*/
#pragma once

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 2;  // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3;  // Connects to module's TX


void speakerSetup();
void runSpeaker();
