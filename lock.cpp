#include "Arduino.h"
#include "lock.h"

bool authorised = false;
bool isCarrying = false;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 48, 47, 46, 45 };  //10,9,8,7
byte colPins[COLS] = { 44, 43, 42, 41 };  //6,5,4,3

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myServo;

LiquidCrystal_I2C lcd(0x27, 20, 4);

MFRC522 mfrc522(SS_PIN, RST_PIN);
/**
  \brief
    This function initializes the TCA9548A multiplexer to use channel 4, the serial port, 
    and the LCD screen. It sets the RFID authorization flag to false and the servo position to 0 degrees. 
    It then initializes the LCD screen and displays a message to prompt the user to scan an RFID tag.
  \param
    None.
  \return
    None.
*/
void lockSetup() {

  // Initialize the SPI communication protocol
  SPI.begin();

  // Initialize the MFRC522 RFID module
  mfrc522.PCD_Init();

  // Initialize the TCA9548A multiplexer to select the desired I2C channel
  TCA9548A(4);

  // Initialize the LCD screen and clear any previous content
  lcd.init();
  lcd.clear();

  // Enable the backlight of the LCD screen
  lcd.backlight();

  // Set the cursor to the first row and first column of the LCD screen
  lcd.setCursor(0, 0);

  // Attach the servo motor to the corresponding pin and move it to the starting position
  myServo.attach(11);
  myServo.write(0);
}
/**
    \brief
      
    \param
      None.
    \return
      A string containing the four digits entered by the user.
*/
String lock_op() {

  // Turn off the lock LED and turn on the green LED
  digitalWrite(24, LOW);
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  String targetWard = "";

  // Select bus 4 for the TCA9548A multiplexer and initialize the LCD
  TCA9548A(4);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);

  // Wait for a short time before printing a loading message on the LCD
  delay(100);
  lcd.print("Loading sensors...");

  // Attach the servo to pin 11 and set its position to 0 degrees
  myServo.attach(11);
  myServo.write(0);

  // Continuously read the RFID tag until a valid tag is detected and its destination is chosen
  while (!isCarrying) {
    // Check if a new card is present and read its content
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

      String content = "";

      // Concatenate the bytes of the card's UID in hexadecimal format
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      // Convert the content to uppercase
      content.toUpperCase();

      // Check if the card is valid and set its destination
      if (content.substring(1) == "37 6A F2 31" || content.substring(1) == "92 6C EB 02") {  // White card,
        // Move the lock servo to 90 degrees to unlock the lock
        myServo.write(90);
        // Display the destination options on the LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Destination");
        lcd.setCursor(0, 1);
        lcd.print("1 = Pharmacy");
        lcd.setCursor(0, 2);
        lcd.print("2 = Radiology");
        lcd.setCursor(0, 3);
        lcd.print("3 = Maternity");

        // Read the keypad to select the destination
        String destination = readKeypad();

        // Set the targetWard based on the selected destination
        if (destination == "1") {
          targetWard = "red";
          // Move the lock servo back to 0 degrees to engage locking mechanism
          myServo.write(0);
          // Display the destination and start carrying the item
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("On Route to");
          lcd.setCursor(0, 1);
          lcd.print("Pharmacy");
          isCarrying = true;

        } else if (destination == "2") {
          targetWard = "blue";
          // Move the lock servo back to 0 degrees to engage locking mechanism
          myServo.write(0);
          // Display the destination and start carrying the item
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("On Route to");
          lcd.setCursor(0, 1);
          lcd.print("Radiology");
          isCarrying = true;

        } else if (destination == "3") {
          targetWard = "blue";
          // Move the lock servo back to 0 degrees to engage locking mechanism
          myServo.write(0);
          // Display the destination and start carrying the item
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("On Route to");
          lcd.setCursor(0, 1);
          lcd.print("Maternity");
          isCarrying = true;
        }
      } else {
        // Display an error message on the LCD if the card is invalid
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Data invalid.");
      }
    }
  }

  isCarrying = false;
  return targetWard;
}
/**
    \brief
      This function reads the input from a 4x4 keypad and returns it as a string. 
      It waits for the user to enter four digits and prints the entered digits to the serial port.
    \param
      None.
    \return
      A string containing the four digits entered by the user.
*/
String readKeypad() {
  String input = "";
  while (input.length() < 1) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      input += key;
    }
  }

  return input;
}
