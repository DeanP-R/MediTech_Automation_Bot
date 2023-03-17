#include <Wire.h>

void TCA9548A(int bus){
  //Serial.begin(9600);
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.println("Selected bus:");
  //Serial.println(bus);
}

