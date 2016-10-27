/*
 * 
 * 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.
 *
 *
 */
 
#include <Wire.h>

void setup() 
{
  // Initialize Serial connection
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Wait for the serial port to connect.
  }

  // Join the I2C bus between microcontrollers
  Wire.begin(); // Address is optional for master
}

void loop() 
{
  String inputString; // String to hold incoming data
  char inChar; // Char to hold each incoming character
  boolean stringComplete = false; // Tell if the incoming string is complete
  
  // If the Teensy receives a message over Serial connection, store it in inputString
  inputString = readStringFromSerial();

  if (inputString.length() != 0)
  {
    Serial.println("The message is: " + inputString);
    Wire.beginTransmission(8); // Transmit the message to the device at address #8 
    Wire.write(inputString.c_str()); // Sends the input string to the 
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

String readStringFromSerial() 
{
  String stringFromSerial;
  // Check if the Serial connection has been established
  while (Serial.available() > 0) 
  {
    stringFromSerial = Serial.readStringUntil('\n');
    return stringFromSerial;
  }
}
