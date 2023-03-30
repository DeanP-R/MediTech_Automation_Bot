
#include "speakers.h"

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;

int music_wait = 1000;
/**
    \brief 
      This function initializes the USB serial port for debugging and the serial port for the DFPlayer Mini. 
      It also starts communication with the DFPlayer Mini and sets its volume to the maximum level. 
      If the communication is established successfully, it plays the "0001.mp3" file located in the "mp3" folder on the SD card.
    \param
      None
    \return
      None
*/
void speakerSetup() {
  // Init USB serial port for debugging
  // Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  player.begin(softwareSerial);

  player.begin(softwareSerial);
}

/**
    \brief
      This function plays an MP3 audio file located in folder number 2 on the DFPlayer Mini, and then waits for 2 seconds before exiting.
    \param
      None
    \return
      None
*/
void runSpeaker(int command, int timing) {   
  player.playMp3Folder(command);
  delay(timing);
  // player.playMp3Folder(1);  //Moving
  // delay(music_wait);
  // player.playMp3Folder(2);  //Obstacle detected
  // delay(music_wait);
  //  player.playMp3Folder(3);  //Please clear path
  //  delay(music_wait);
  //  player.playMp3Folder(4);  //Please scan RFID tag
  //  delay(music_wait);
  //  player.playMp3Folder(5);  //Please enter your PIN
  //  delay(music_wait);
  //  player.playMp3Folder(6);  //Unlocking
  //  delay(music_wait);
  //  player.playMp3Folder(7);  //Locking
  //  delay(music_wait);
  //  player.playMp3Folder(8);  //Delivery in progress
  //  delay(music_wait);
  //  player.playMp3Folder(9);  //Delivery complete
  //  delay(music_wait);
  //  player.playMp3Folder(10); //On route to
  //  delay(music_wait);
  //  player.playMp3Folder(11); //Arrived at
  //  delay(music_wait);
  //  player.playMp3Folder(12); //A & E
  //  delay(music_wait);
  //  player.playMp3Folder(13); //Pharmacy
  //  delay(music_wait);
  //  player.playMp3Folder(14); //Maternity
  //  delay(music_wait);
  //  player.playMp3Folder(15); //Radiology
  //  delay(music_wait);
  //  player.playMp3Folder(16); //Outpatients
  //  delay(music_wait);
  //  player.playMp3Folder(17); //Home
  //  delay(music_wait);
  //  player.playMp3Folder(18); //Re-calculating route
  //  delay(music_wait);
  //  player.playMp3Folder(19); //Correct tag deteced
  //  delay(music_wait);
  //  player.playMp3Folder(20); //Correct pin detected
  //  delay(music_wait);
  //  player.playMp3Folder(21); //Incorrect tag detected
  //  delay(music_wait);
  //  player.playMp3Folder(22); //Incorrect pin detected
  //  delay(music_wait);
  //  player.playMp3Folder(23); //Access granted
  //  delay(music_wait);
  //  player.playMp3Folder(24); //Access denied
  //  delay(music_wait);
  //  player.playMp3Folder(25); //Battery fully charged
  //  delay(music_wait);
}