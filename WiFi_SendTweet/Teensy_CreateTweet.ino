#include <Wire.h>
#include "Keyboard.h"

byte x = 0;

void loop()
{
}

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Keyboard.begin();  // Initialize control over keyboard
  
  Serial.begin(9600);  // start serial for output
}

void loop() 
{
  // check for incoming serial data:
  if (Serial.available() > 0) 
  {
    // read incoming serial data:
    char userInput = Serial.read();
    // Type the next ASCII value from what you received:
    Keyboard.write(userInput + 1);
  }

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("The tweet follows"); // Send 17 bytes
  Wire.write(userInput); // Send varying # of bytes (depends on size of string)
  Wire.endTransmission(); // stop transmitting
  
  delay(500);
}
