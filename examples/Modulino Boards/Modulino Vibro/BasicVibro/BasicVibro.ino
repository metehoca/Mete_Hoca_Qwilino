/*
  Qwilino_Vibro - Basic Usage Example
  
  This example demonstrates how to initialize and control the Modulino 
  Vibro module using the lightweight Qwilino library. It showcases 
  setting vibration intensity, running the motor for a specific 
  duration, and controlling it manually.
*/

#include <Wire.h>
#include "Qwilino_Vibro.h"

// Create an instance of the Qwilino_Vibro class.
// The default I2C address (0x38) is assigned automatically by the constructor.
Qwilino_Vibro vibro;

void setup() {
  // Initialize serial communication for debugging purposes at 115200 baud rate.
  Serial.begin(115200);

  // Wait for the serial monitor to open (useful for boards with native USB like Uno R4).
  while (!Serial) {
    delay(10);
  }

  Serial.println("Qwilino Vibro Module Test Initializing...");

  // Initialize the Qwiic/I2C bus and check if the module is connected.
  // The appropriate Wire port (Wire or Wire1) is automatically selected 
  // by the library based on your microcontroller architecture.
  if (!vibro.begin()) {
    Serial.println("Error: Vibro module not found on the I2C bus!");
    Serial.println("Please check your Qwiic cables and connections.");
    
    // Halt the system in an infinite loop if the module is missing.
    while (1) {
      delay(100);
    }
  }

  Serial.println("Success: Vibro module is connected and ready.");

  // Set the initial vibration intensity.
  // The setIntensity function accepts a PWM value from 0 (off) to 255 (maximum power).
  vibro.setIntensity(150);
  Serial.println("Status: Intensity set to 150.");
}

void loop() {
  Serial.println("Action: Vibrate for 500 milliseconds.");
  
  // Turn on the motor for exactly 500ms. 
  // The library automatically handles turning the motor off after the delay.
  vibro.on(500);

  // Pause for 1 second before the next action.
  delay(1000); 

  Serial.println("Action: Increase intensity to maximum (255) and vibrate continuously.");
  
  // Change the vibration intensity on the fly.
  vibro.setIntensity(255);

  // Calling on() with no arguments (or 0) turns the motor on indefinitely.
  vibro.on();

  // Let the motor run continuously for 1 second.
  delay(1000); 

  Serial.println("Action: Stop vibration manually.");
  
  // Explicitly send the off command to stop the motor.
  vibro.off();

  // Wait for 2 seconds before restarting the main loop.
  delay(2000); 

  // Reset the intensity back to the default level for the next loop iteration.
  vibro.setIntensity(150);
}