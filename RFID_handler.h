#ifndef RFID_HANDLER_H
#define RFID_HANDLER_H

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setupRFID();
bool checkAuthorized();

#endif

void setupRFID() {
  SPI.begin();
  mfrc522.PCD_Init();
}

bool checkAuthorized() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  if (content.substring(1) == "F4 11 4F 60") {
    if(!authorised){
      Serial.println("Authorized access");
      myservo.write(180);
      authorised = true;
    }
    else{
      Serial.println("Storage Locked");
      myservo.write(0);
      authorised = false;
    }
    delay(3000);
  } else {
    Serial.println("Access denied");
    myservo.write(0);
    authorised = false;
    delay(3000);
  }
}
