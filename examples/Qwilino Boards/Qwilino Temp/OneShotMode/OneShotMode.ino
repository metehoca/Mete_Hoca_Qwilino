/*
  Qwilino Temp - One-Shot Mode (Power Saving) Example
  
  This example demonstrates how to:
  1. Put the sensor into shutdown mode to save power.
  2. Trigger a single conversion (one-shot) only when needed.
  3. Read the result and return to sleep mode.
*/

#include <Qwilino_Temp.h>

Qwilino_Temp sensor;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Qwilino Temp One-Shot Mode Starting...");

  if (!sensor.begin()) {
    Serial.println("ERROR: Qwilino Temp not found!");
    while (1) delay(100);
  }

  // Put the sensor into shutdown mode immediately to save power
  sensor.shutdown(true);
  Serial.println("Sensor is now in shutdown mode.\n");
}

void loop() {
  Serial.println("Waking up sensor for a one-shot reading...");

  // Trigger a one-shot reading. The sensor will briefly wake up, 
  // measure the temperature, and then go back to sleep automatically.
  float tempC = sensor.oneShot();

  Serial.print("One-Shot Temperature: ");
  Serial.print(tempC, 2);
  Serial.println(" *C\n");

  // Wait 5 seconds before the next reading to demonstrate power saving
  delay(5000); 
}