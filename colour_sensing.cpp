// Set to false if using a common cathode LED. - Example colorview code
#define commonAnode true

// Our RGB -> eye-recognized gamma color. - Example colorview code
byte gammatable[256];

// Create a colour sensor object. - Example colorview code
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

/*
 * This method starts the colour sensor,
 * Assigns and initialises the colour sensor pins, 
 * Then creates a gamma table to convert the RGB data into observable human colours. - Example colorview code
 */
void setupColourSensor() {
  tcs.begin();
  
  // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
}

/*
 * This method reads the colour sensor, 
 * Then populates a provided array with RGB values for the rest of the program to use. - Example colorview code
 */
void readColourSensor(int* RGB) {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED

  RGB[0] = int(red);
  RGB[1] = int(green);
  RGB[2] = int(blue);

#if defined(ARDUINO_ARCH_ESP32)
  ledcWrite(1, gammatable[(int)red]);
  ledcWrite(2, gammatable[(int)green]);
  ledcWrite(3, gammatable[(int)blue]);
#else
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
#endif 

  return RGB;
}
