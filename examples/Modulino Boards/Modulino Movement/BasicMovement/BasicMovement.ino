/*
  Qwilino Movement - Basic Test
  
  IMPORTANT: You must install the "Arduino_LSM6DSOX" library 
  from the Arduino Library Manager before running this sketch.

  This example demonstrates how to:
  1. Initialize the Movement (6-Axis IMU) module.
  2. Read accelerometer values (G-force).
  3. Read gyroscope values (degrees per second).
*/

#include <Qwilino_Movement.h>

QwilinoMovement movement;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("Qwilino Movement Test Starting...");

  // Initialize the sensor. It automatically selects the correct I2C port (Wire or Wire1).
  if (!movement.begin()) {
    Serial.println("ERROR: Movement module not found!");
    Serial.println("1. Check your I2C connections.");
    Serial.println("2. Make sure 'Arduino_LSM6DSOX' library is installed.");
    while (1) delay(100);
  }

  Serial.println("Module is ready. Reading data...\n");
  delay(100);
}

void loop() {
  // Check if new data is available and read it from the sensor
  if (movement.update()) {
    
    // Print Accelerometer Data (G-Force)
    Serial.print("Acc [X: ");
    Serial.print(movement.getX(), 2);
    Serial.print(" Y: ");
    Serial.print(movement.getY(), 2);
    Serial.print(" Z: ");
    Serial.print(movement.getZ(), 2);
    Serial.print("]  |  ");
    
    // Print Gyroscope Data (Degrees / Second)
    Serial.print("Gyro [Roll: ");
    Serial.print(movement.getRoll(), 2);
    Serial.print(" Pitch: ");
    Serial.print(movement.getPitch(), 2);
    Serial.print(" Yaw: ");
    Serial.print(movement.getYaw(), 2);
    Serial.println("]");
  }

  // Small delay to make the Serial Monitor output readable
  delay(100);
}