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

void lockSetup() {

  // Serial.begin(9600);
  SPI.begin();

  mfrc522.PCD_Init();

  TCA9548A(4);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);

  TCA9548A(4);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);  
  
  delay(100);
  lcd.print("Loading sensors...");   

  myServo.attach(11);
  myServo.write(0);
}

String lock_op() {

  digitalWrite(24, LOW);
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);  
  String targetWard = "";

  TCA9548A(4);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place RFID Tag");

  while (!isCarrying) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {

      String content = "";

      for (byte i = 0; i < mfrc522.uid.size; i++) {

        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));

      }
      content.toUpperCase();

      if (content.substring(1) == "37 6A F2 31" || content.substring(1) == "92 6C EB 02") {// White card, 

        myServo.write(90);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Destination");
        lcd.setCursor(0, 1);
        lcd.print("1 = Pharmacy");
        lcd.setCursor(0, 2);
        lcd.print("2 = Radiology");
        lcd.setCursor(0, 3);
        lcd.print("3 = Maternity");  

        String destination = readKeypad();

        if (destination == "1") {
          targetWard = "red";
          myServo.write(0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("On Route to");
          lcd.setCursor(0, 1);
          lcd.print("Pharmacy");
          isCarrying = true;
            
        } else if (destination == "2") {
          targetWard = "blue";  
          myServo.write(0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("On Route to");
          lcd.setCursor(0, 1);
          lcd.print("Radiology");
          isCarrying = true;
                  
        } else if (destination == "3") {
          targetWard = "blue";
          myServo.write(0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("On Route to");
          lcd.setCursor(0, 1);
          lcd.print("Maternity");
          isCarrying = true;
        }     
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Data invalid.");
      }
    }  
  }

  isCarrying = false;
  return targetWard;
}

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
