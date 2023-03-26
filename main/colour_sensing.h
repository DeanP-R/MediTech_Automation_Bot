#pragma once 

// Include the libraries. - Example colorview code
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_TCS34725.h"
#include "multiplexer.h"

// // Define colour sensor output pins. - Example colorview code
// #define redpin 3
// #define greenpin 5
// #define bluepin 6

void setupColourSensor();
void readColourSensor();
void detectColour();
