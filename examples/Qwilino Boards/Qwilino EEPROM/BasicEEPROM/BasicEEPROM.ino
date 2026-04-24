/*
 * Qwilino EEPROM Library - Educational Example
 * * This sketch demonstrates:
 * 1. Automatic I2C port detection (Wire vs Wire1).
 * 2. Basic byte storage using updateByte (saves write cycles).
 * 3. Advanced structure storage using put/get templates.
 * 4. Reading data back for verification.
 * 5. Safety checks against memory overflow.
 */

#include <Qwilino_EEPROM.h>

// Create EEPROM object with default address 0x50
QwilinoEEPROM memory;

// Define a custom structure to simulate device settings
struct DeviceSettings {
  int deviceID;
  float calibrationValue;
  char unitName[10];
  bool isActive;
};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("\n--- Qwilino EEPROM Demo Started ---");

  /* * STEP 1: INITIALIZATION
   * calling begin() without arguments allows the library to automatically
   * select 'Wire1' for Uno R4 WiFi/Nano R4 or 'Wire' for standard boards.
   */
  if (!memory.begin()) {
    Serial.println("CRITICAL ERROR: EEPROM module not found!");
    Serial.println("Please check your wiring or Qwiic connection.");
    while (1); // Stop execution
  }
  
  Serial.println("SUCCESS: EEPROM connected and ready.");

  // --- STEP 2: BASIC BYTE STORAGE ---
  Serial.println("\n[Test 1] Basic Byte Operation");
  
  uint8_t volumeLevel = 75;
  uint16_t byteAddr = 0; // Storing at address 0

  Serial.print("Writing volume level: ");
  Serial.println(volumeLevel);

  // updateByte only writes if the new value is different from the stored one.
  memory.updateByte(byteAddr, volumeLevel);

  // Read it back
  uint8_t readVolume = memory.readByte(byteAddr);
  Serial.print("Read volume level: "); 
  Serial.println(readVolume);

  if (volumeLevel == readVolume) {
    Serial.println("-> Byte verification passed.");
  } else {
    Serial.println("-> Byte verification FAILED.");
  }

  // --- STEP 3: ADVANCED OBJECT STORAGE ---
  Serial.println("\n[Test 2] Storing Complex Structures (Struct)");

  // Create a settings object with sample data
  DeviceSettings myConfig;
  myConfig.deviceID = 1042;
  myConfig.calibrationValue = 23.56;
  strcpy(myConfig.unitName, "Sensor_A");
  myConfig.isActive = true;

  uint16_t structAddr = 10; // Start at address 10 to avoid overlap

  Serial.println("Saving configuration object...");
  memory.put(structAddr, myConfig);

  // Clear local variable to ensure we are really reading from EEPROM
  DeviceSettings readConfig; 
  
  Serial.println("Reading configuration object...");
  memory.get(structAddr, readConfig);

  // Print results
  Serial.print(" ID: "); Serial.println(readConfig.deviceID);
  Serial.print(" Name: "); Serial.println(readConfig.unitName);
  Serial.print(" Calib: "); Serial.println(readConfig.calibrationValue);
  Serial.print(" Active: "); Serial.println(readConfig.isActive ? "Yes" : "No");

  // --- STEP 4: SAFETY BOUNDS CHECK ---
  Serial.println("\n[Test 3] Out of Bounds Protection");
  
  // Try to write beyond the 32KB limit (Address 32768 is out of bounds)
  bool safeWrite = memory.updateByte(40000, 0xFF);

  if (!safeWrite) {
    Serial.println("Safety System Works: Prevented write to invalid address.");
  } else {
    Serial.println("Warning: Write check failed.");
  }

  Serial.println("\n--- All Tests Completed ---");
}

void loop() {
  // Nothing to do here
}