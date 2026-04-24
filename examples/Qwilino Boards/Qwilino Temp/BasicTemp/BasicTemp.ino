/*
  Qwilino Temp - Basic Reading Example
  
  This example demonstrates how to:
  1. Initialize the Modulino Temp (TMP1075) sensor.
  2. Continuously read the temperature in Celsius, Fahrenheit, and Kelvin.
*/

#include <Qwilino_Temp.h>

Qwilino_Temp sensor;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); 

  Serial.println("Qwilino Temp Test Starting...");

  // Initialize the sensor. It automatically selects the correct I2C port.
  if (!sensor.begin()) {
    Serial.println("ERROR: Qwilino Temp not found!");
    Serial.println("1. Check your I2C connections.");
    Serial.println("2. Check if the I2C address is correct (Default: 0x49).");
    while (1) delay(100);
  }
  
  Serial.println("Sensor is ready. Reading data...\n");
}

void loop() {
  // Read temperature in different units
  float tempC = sensor.readTempC();
  float tempF = sensor.readTempF();
  float tempK = sensor.readTempK();

  // Print results to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(tempC, 2); Serial.print(" *C  |  ");
  Serial.print(tempF, 2); Serial.print(" *F  |  ");
  Serial.print(tempK, 2); Serial.println(" K");

  delay(1000); // Wait 1 second before next reading
}