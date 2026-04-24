/*
  Qwilino_Relay - Basic Usage Example
  
  This example demonstrates how to initialize and control the Modulino 
  Latch Relay module using the lightweight Qwilino library. A latch 
  relay magnetically holds its position, meaning it only requires 
  power when switching between SET and RESET states.
*/

#include <Wire.h>
#include "Qwilino_Relay.h"

// Create an instance of the Qwilino_Relay class.
Qwilino_Relay relay;

void setup() {
  // Initialize serial communication at 115200 baud rate.
  Serial.begin(115200);

  // Wait for the serial monitor to open.
  while (!Serial) {
    delay(10);
  }

  Serial.println("Qwilino Latch Relay Module Initialization...");

  // Initialize the Qwiic/I2C bus.
  if (!relay.begin()) {
    Serial.println("Error: Relay module not found on the I2C bus!");
    Serial.println("Please check your Qwiic cables.");
    
    // Halt the execution if the module cannot be detected.
    while (1) {
      delay(100);
    }
  }

  Serial.println("Success: Relay module is connected and ready.");
  
  // Ensure the relay starts in a safe, disconnected state.
  relay.reset();
  Serial.println("Relay Initial State: RESET (Open)");
}

void loop() {
  Serial.println("Action: Setting Relay (Closing the circuit)");
  
  // The set() function activates the relay coil to close the contacts.
  relay.set();
  
  // Print current logical state
  Serial.print("Current State: ");
  Serial.println(relay.getState() ? "SET" : "RESET");
  
  // Wait for 3 seconds while the circuit is closed.
  delay(3000); 

  Serial.println("Action: Resetting Relay (Opening the circuit)");
  
  // The reset() function activates the reverse coil to open the contacts.
  relay.reset();

  // Print current logical state
  Serial.print("Current State: ");
  Serial.println(relay.getState() ? "SET" : "RESET");

  // Wait for 3 seconds while the circuit is open.
  delay(3000); 
}