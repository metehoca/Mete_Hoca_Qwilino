/*
  Qwilino Distance - Basic Measurement Example
  
  IMPORTANT: You must install the "STM32duino VL53L4CD" library 
  from the Arduino Library Manager before running this sketch.

  This example demonstrates how to:
  1. Initialize the Time-of-Flight distance sensor.
  2. Continuously check for new measurements.
  3. Print the measured distance in millimeters (mm).
*/

#include <Qwilino_Distance.h>

QwilinoDistance distanceSensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwilino Distance Test Starting...");

  // Initialize the sensor. It automatically selects the correct I2C port.
  // Note: This process takes 1-2 seconds as it loads firmware to the sensor.
  if (!distanceSensor.begin()) {
    Serial.println("ERROR: Sensor not found or initialization failed!");
    Serial.println("1. Check your I2C connections (SDA/SCL).");
    Serial.println("2. Make sure 'STM32duino VL53L4CD' library is installed.");
    while (1) delay(100); // Halt the program
  }

  Serial.println("Sensor is ready. Starting measurements...\n");
}

void loop() {
  // Check if a new measurement is ready from the sensor.
  // It's highly recommended to use available() instead of blocking delays.
  if (distanceSensor.available()) {
    
    // Get the measured distance in millimeters
    int distance_mm = distanceSensor.get();
    
    Serial.print("Distance: ");
    Serial.print(distance_mm);
    Serial.println(" mm");
  }

  // Small delay for loop stability. 
  // The sensor is set to a 50ms timing budget in the library.
  delay(10); 
}