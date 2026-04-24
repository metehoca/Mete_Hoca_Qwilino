/*
  Qwilino_Light - Basic Sensor Reading Example
  
  This example demonstrates how to initialize the Modulino Light 
  (LTR-381RGB-01) sensor using the lightweight Qwilino library.
  It continuously reads and prints ambient light, RGB color data, 
  and infrared levels to the Serial Monitor.
*/

#include <Wire.h>
#include "Qwilino_Light.h"

// Create an instance of the Qwilino_Light sensor class.
// The default I2C address (0x53) is assigned automatically.
Qwilino_Light lightSensor;

void setup() {
  // Initialize serial communication at 115200 baud rate.
  Serial.begin(115200);

  // Wait for the serial monitor to open (important for native USB boards).
  while (!Serial) {
    delay(10);
  }

  Serial.println("Qwilino Light Sensor Initialization...");

  // Initialize the Qwiic/I2C bus.
  // The library automatically resolves the correct Wire port (e.g., Wire1 for Nano R4).
  if (!lightSensor.begin()) {
    Serial.println("Error: Light sensor not found on the I2C bus!");
    Serial.println("Please check your Qwiic cables.");
    
    // Halt the execution if the sensor cannot be detected.
    while (1) {
      delay(100);
    }
  }

  Serial.println("Success: Light sensor is connected and ready.");
  Serial.println("--------------------------------------------------");
}

void loop() {
  // Read the 20-bit raw values from the sensor's registers
  uint32_t ambientLight = lightSensor.getAmbient();
  uint32_t redLevel = lightSensor.getRed();
  uint32_t greenLevel = lightSensor.getGreen();
  uint32_t blueLevel = lightSensor.getBlue();
  uint32_t irLevel = lightSensor.getInfrared();

  // Print the collected data to the Serial Monitor
  Serial.print("Ambient: ");
  Serial.print(ambientLight);
  
  Serial.print(" | R: ");
  Serial.print(redLevel);
  
  Serial.print(" G: ");
  Serial.print(greenLevel);
  
  Serial.print(" B: ");
  Serial.print(blueLevel);
  
  Serial.print(" | IR: ");
  Serial.println(irLevel);

  // Wait 500 milliseconds before taking the next reading
  delay(500);
}