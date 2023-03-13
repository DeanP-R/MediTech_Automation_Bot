#include "proportional_line_following.h"
#include "Adafruit_VL53L0X.h"

void setupLasers();
void readLaserSensors(int* LCR);
void swerveLeft();
void swerveRight();