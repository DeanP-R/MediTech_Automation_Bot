
#include "lock.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {48, 47, 46, 45};       //10,9,8,7
byte colPins[COLS] = {44, 43, 42, 41};        //6,5,4,3

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void lockSetup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(11);
  Serial.println("RFID reading UID");
  
  myServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Scan RFID tag");  
} 

void lock_op() {
  
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {      
      if (mfrc522.uid.size == 4) {
        byte expectedUID[] = {0x92, 0x6C, 0xEB, 0x02}; // expected UID
        byte tagUID[4];
        memcpy(tagUID, mfrc522.uid.uidByte, 4); // copy scanned UID to tagUID array

        if (memcmp(expectedUID, tagUID, 4) == 0) { // compare expectedUID to scanned UID
          Serial.println("Authorized tag scanned.");
          lcd.clear();
          lcd.print("Correct tag");
          delay(3000);
          lcd.clear();
          
          Serial.println("Please enter the PIN");   // ask for PIN and check if it is correct
          lcd.print("Enter the PIN: ");
          String pin = readKeypad();
          if (pin == "1234") {
            Serial.println("PIN correct. Unlocking servo.");
            lcd.clear();
            lcd.print("Correct PIN");
            
            myServo.write(90);
            delay(5000);
            myServo.write(0);
          }
          else {
            Serial.println("PIN incorrect. Access denied.");
            lcd.setCursor(0,0);
            lcd.print("Incorrect PIN");
            delay(3000);
          }
        }
        else {
          Serial.println("Unauthorized tag scanned.");
          lcd.clear();
          lcd.print("Unauthorised tag");
        }
      }
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
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

