#include "RFID_handler.h"

/*
  Additional functions for RFID handling and processing.
  <>rfid_setup:
        initializes the RFID reader and servo motor by starting the SPI communication,
        initializing the RFID reader, attaching the servo to a pin, setting the servo's 
        initial position to 0 degrees, and printing a message to the serial monitor 
        asking the user to approach their card to the reader.
  <>check_user:
         This function checks if a new card is present and if it can be read by the RFID reader.
         If a card is present and can be read, the function reads the card's unique ID, 
         converts it to a string, and compares it to a predefined authorized ID. 
         If the card's ID matches the authorized ID, the servo motor moves to 180 degrees, 
         and the authorized variable is set to true. If the card's ID does not match the authorized ID, 
         the servo motor moves to 0 degrees, the authorized variable is set to false, 
         and a message is printed to the serial monitor indicating that access was denied.
*/

void rfid_setup() {

  // Start the SPI communication
  SPI.begin();

  // Initialize the MFRC522 RFID module
  mfrc522.PCD_Init();

  // Attach the servo to the pin specified by SERVO_PIN
  myservo.attach(SERVO_PIN);

  // Set the servo to the initial position (0 degrees)
  myservo.write(0);
  Serial.println("Approximate your card to the reader...\n");
}

bool check_user() {
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    // If no new card is present, return false
    return false;
  }
  // Read the serial number of the card
  if (!mfrc522.PICC_ReadCardSerial()) {
    // If the card's serial number couldn't be read, return false
    return false;
  }

  // Create an empty string to store the card's serial number
  String content = "";

  // Iterate through the bytes of the card's serial number
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // Add a leading 0 if the current byte is less than 0x10
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    // Append the current byte of the serial number to the string in hexadecimal format
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  // Change the serial number to uppercase
  content.toUpperCase();

  // Compare the card's serial number to a predefined value
  if (content.substring(1) == "F4 11 4F 60") {
    // If the card's serial number matches the predefined value and the access is not authorised
    if (!authorised) {
      // Print a message to the serial monitor
      Serial.println("Authorized access");
      // Move the servo to 180 degrees
      myservo.write(180);
      // Set the authorised variable to true
      authorised = true;
      // Wait for 3 seconds
      delay(3000);
    }
    // If the card's serial number matches the predefined value and the access is already authorised
    else {
      // Print a message to the serial monitor
      Serial.println("Storage Locked");
      // Move the servo to 0 degrees
      myservo.write(0);
      // Set the authorised variable to false
      authorised = false;
      // Wait for 3 seconds
      delay(3000);
    }
  } else {
    // If the card's serial number doesn't match the predefined value
    // Print a message to the serial monitor
    Serial.println("Access denied");
    // Move the servo to 0 degrees
    myservo.write(0);
    // Set the authorised variable to false
    authorised = false;
    // Wait
    delay(3000);
  }
}