/*
  Qwilino_Joystick - Basic Usage Example
  
  This example demonstrates how to initialize and read data from the Modulino 
  Joystick module using the lightweight Qwilino library. It reads the X and Y 
  axis values along with the push button state, printing them to the Serial Monitor.
*/

#include <Wire.h>
#include "Qwilino_Joystick.h"

// Create an instance of the Qwilino_Joystick class.
// The default I2C address is automatically handled by the constructor.
Qwilino_Joystick joystick;

void setup() {
  // Initialize serial communication at 115200 baud rate for faster data transfer.
  Serial.begin(115200);

  // Wait for the serial monitor to open (essential for native USB boards).
  while (!Serial) {
    delay(10);
  }

  Serial.println("Qwilino Joystick Module Initialization...");

  // Initialize the Qwiic/I2C bus.
  // The library automatically resolves the correct Wire port (e.g., Wire1 for Nano R4).
  if (!joystick.begin()) {
    Serial.println("Error: Joystick module not found on the I2C bus!");
    Serial.println("Please check your Qwiic cables.");
    
    // Halt the execution if the module cannot be detected.
    while (1) {
      delay(100);
    }
  }

  Serial.println("Success: Joystick module is connected and ready.");
}

void loop() {
  // Read the raw 16-bit analog-to-digital (ADC) values from the X and Y axes.
  int16_t xValue = joystick.getX();
  int16_t yValue = joystick.getY();
  
  // Read the digital state of the built-in push button.
  // Returns true if the button is pressed, false otherwise.
  bool isPressed = joystick.getButton();

  // Print the retrieved data to the Serial Monitor in a readable format.
  Serial.print("X-Axis: ");
  Serial.print(xValue);
  
  Serial.print("\tY-Axis: ");
  Serial.print(yValue);
  
  Serial.print("\tButton Pressed: ");
  if (isPressed) {
    Serial.println("YES");
  } else {
    Serial.println("NO");
  }

  // A brief delay to prevent flooding the Serial Monitor.
  delay(100);
}