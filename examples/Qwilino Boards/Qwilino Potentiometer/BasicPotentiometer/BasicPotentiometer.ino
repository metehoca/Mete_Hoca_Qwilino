/*
  Qwilino Potentiometer Example
  
  This example demonstrates the simplest way to read an analog value 
  from the Qwilino Potentiometer (ADS1015) module. The library is 
  designed to output a 10-bit value (0-1023) to perfectly mimic 
  a standard Arduino analogRead(), making it highly compatible 
  with existing beginner tutorials and projects.
*/

#include "Qwilino_Potentiometer.h"

// Create the potentiometer object
Qwilino_Potentiometer pot;

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  
  // Initialize the sensor (automatically detects the correct Wire port)
  if (!pot.begin()) {
    Serial.println("Connection error! Please check the I2C wiring.");
    while (1); // Halt the program if the sensor is not found
  }
}

void loop() {
  // Read the mapped 10-bit value (0 to 1023)
  int value = pot.read(); 
  
  // Print the value to the Serial Monitor
  Serial.println(value);
  
  // A short delay to stabilize the serial output
  delay(10);
}