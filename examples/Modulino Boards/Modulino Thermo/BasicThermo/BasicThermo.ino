/*
  Qwilino Thermo - Basic Reading Example
  
  This example demonstrates how to:
  1. Initialize the Modulino Thermo sensor.
  2. Read temperature (Celsius) and humidity (%) values.
  3. Use the efficient update() method to fetch both values in a single I2C request.
*/

#include <Qwilino_Thermo.h>

QwilinoThermo thermo;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Qwilino Thermo Test Starting...");

  // Initialize the sensor. It automatically selects the correct I2C port (Wire or Wire1).
  // Default I2C address is 0x44.
  if (!thermo.begin()) {
    Serial.println("ERROR: Thermo module not found!");
    Serial.println("Please check your I2C connections.");
    while (1) delay(100);
  }

  Serial.println("Thermo module is ready. Reading data...\n");
}

void loop() {
  // The update() function triggers a single measurement 
  // and updates both temperature and humidity variables internally.
  // This is much faster and more efficient than calling 
  // getTemperature() and getHumidity() separately.
  thermo.update(); 
  
  float temperature = thermo.readLastTemperature();
  float humidity = thermo.readLastHumidity();

  // Print results to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print("°C  |  Humidity: ");
  Serial.print(humidity, 2);
  Serial.println("%");

  // Wait 1 second before the next measurement
  delay(1000);
}