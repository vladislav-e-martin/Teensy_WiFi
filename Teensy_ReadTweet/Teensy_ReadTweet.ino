/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */
 
#include <Wire.h>

char* inputString = ""; // A string to hold incoming data
boolean stringComplete = false;  // Whether the string is complete

void setup() 
{
  // Initialize Serial connection
  Serial.begin(9600);
  // Reserve 1000 bytes (250 characters) for the inputString
  // inputString.reserve(1000);

  // Code to receive the message from the Tx node
  // If a message is received, store it in inputString and set stringComplete = true
  // Otherwise, stringComplete = false

  // Join the I2C bus between microcontrollers
  Wire.begin(); // Address is optional for master
}

void loop() 
{
  // print the string when a newline arrives:
  if (stringComplete)
  {
    Serial.println(inputString);

    Wire.beginTransmission(8); // Transmit the message to the device at address #8
    Wire.write("The message is: "); // Send 16 bytes 
    Wire.write(inputString); // Send 1000 bytes
    Wire.endTransmission(); // Stop transmitting the message
    
    // Clear the contents of the inputString
    inputString = "";
    // Reset the Serial.read() completion indicator, stringComplete
    stringComplete = false;
  }

  delay(500);
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
*/

void serialEvent() 
{
  // Check if the Serial connection has been established
  while (Serial.available()) 
  {
    // Read the newest byte
    char inChar = (char)Serial.read();
    // Add the newest byte to the inputString
    inputString += inChar;
    // If the newest byte is a newline, then the user has finished typing the inputString
    if (inChar == '\n')
    {
      // Indicate that the user has finished typing the inputString
      stringComplete = true;
    }
  }
}
