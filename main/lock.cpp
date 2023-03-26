#include "Arduino.h"
#include "lock.h"

MFRC522 mfrc522(53, RST_PIN);
bool authorised = false;

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

void lockSetup() {
  // Channel 6?
  Serial.println("selecting channel");
  TCA9548A(5);
  Serial.println("selected channel 5");
  //Serial.begin(9600);
  //SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(11);
  Serial.println("ballz RFID reading UID");
  authorised = false;
  myServo.write(0);
  // Channel 5?
  Serial.print("selecting channel");
  TCA9548A(4);  
  Serial.println("selected channel 4");
  lcd.init();
  delay(3000);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ballz Scan RFID tag");

}

void lock_op() {
Serial.print("selecting channel");
TCA9548A(5);
Serial.println("channel selected");
    if (mfrc522.PICC_IsNewCardPresent()) {
      if (mfrc522.PICC_ReadCardSerial()) {
        if (mfrc522.uid.size == 4) {
          byte expectedUID[] = { 0x92, 0x6C, 0xEB, 0x02 };  // expected UID
          byte tagUID[4];
          memcpy(tagUID, mfrc522.uid.uidByte, 4);  // copy scanned UID to tagUID array

          if (memcmp(expectedUID, tagUID, 4) == 0) {  // compare expectedUID to scanned UID
            if(!authorised){
              Serial.println("Authorized tag scanned.");
              TCA9548A(4);
              lcd.clear();
              lcd.print("Correct tag");
              delay(3000);
              lcd.clear();
              Serial.println("Please enter the PIN");  // ask for PIN and check if it is correct
              lcd.print("Enter the PIN: ");
              String pin = readKeypad();
              if (pin == "123A") {
                Serial.println("PIN correct. Unlocking servo.");
                lcd.clear();
                lcd.print("Correct PIN");
                authorised = true;
                myServo.write(90);
                delay(5000);
              } else {
                Serial.println("PIN incorrect. Access denied.");
                lcd.setCursor(0, 0);
                lcd.print("Incorrect PIN");
                authorised = false;
                delay(3000);
              }
            }
            else {
              lcd.print("Storage Locked");
              myServo.write(0);
              authorised = false;
            }
          }
          else {
            Serial.println("Unauthorized tag scanned.");
            lcd.clear();
            lcd.print("Unauthorised tag");
            myServo.write(0);
            authorised = false;
          }
        TCA9548A(5);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
      }
    }
  }
}

String readKeypad() {
  String input = "";
  while (input.length() < 4) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      input += key;
      Serial.print(key);
    }
  }
  Serial.println();
  return input;
}
