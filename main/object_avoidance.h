#include "proportional_line_following.h"
#include "Adafruit_VL53L0X.h"
#include "multiplexer.h"
#include "speakers.h"

void setupLasers();
void readLaserSensors();
void swerveLeft();
void swerveRight();
void avoidance();