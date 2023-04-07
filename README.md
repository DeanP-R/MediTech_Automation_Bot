#                                                            System Project Arduino
  _This repository contains the code for an Arduino-based system project that incorporates object avoidance, line following, RFID tag detection, colour         sensing, and audio feedback. The code is written in C++ and consists of multiple files, each containing classes and methods specific to the system's         functionality._

## File structure

    <>System_Project_Arduino.ino  
      The main file that runs the system.
    <>colour_sensing.cpp: 
      Contains the implementation of the ColourSensing class, which is responsible for detecting the colour of an object using an RGB colour sensor.
    <>colour_sensing.h: 
      Contains the header file for the ColourSensing class.
    <>lock.cpp: 
      Contains the implementation of the Lock class, which is responsible for locking and unlocking a cabinet using an RFID tag.
    <>lock.h: 
      Contains the header file for the Lock class.
    <>multiplexer.cpp: 
      Contains the implementation of the Multiplexer class, which is responsible for selecting and reading data from a specific sensor among a set of sensors.
    <>multiplexer.h: 
      Contains the header file for the Multiplexer class.
    <>object_avoidance.cpp: 
      Contains the implementation of the ObjectAvoidance class, which is responsible for detecting and avoiding obstacles using an ultrasonic sensor.
    <>object_avoidance.h: 
      Contains the header file for the ObjectAvoidance class.
    <>proportional_line_following.cpp: 
      Contains the implementation of the ProportionalLineFollowing class, which is responsible for following a line using two IR sensors and a PID controller.
    <>proportional_line_following.h: 
      Contains the header file for the ProportionalLineFollowing class.
    <>speakers.cpp: 
      Contains the implementation of the Speakers class, which is responsible for playing audio feedback using a DFPlayer Mini MP3 player module.
    <>speakers.h: 
      Contains the header file for the Speakers class.

## How to use

  _To use this code, download the repository and upload the System_Project_Arduino.ino file to an Arduino Mega board. Make sure to include all necessary libraries.
  The system is designed to follow a line until it detects an obstacle, at which point it will use object avoidance to avoid the obstacle. It can also detect the colour of an object, lock and unlock a cabinet using an RFID tag, and provide audio feedback._
  
## Required Libraries

- <SPI.h>
- <MFRC522.h>
- <Keypad.h>
- <Servo.h>
- <LiquidCrystal_I2C.h>
- <Wire.h>
