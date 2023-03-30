#include <Wire.h>
/**
  \brief
    This function selects one of the I2C buses on the TCA9548A multiplexer by sending a byte to its address. 
    The function takes an integer parameter bus that specifies the channel to select on the multiplexer.
  \param
    bus: An integer value that specifies the channel (0-7) to select on the TCA9548A multiplexer.
  \return:
    None
*/
void TCA9548A(int bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

