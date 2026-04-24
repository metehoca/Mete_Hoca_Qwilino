/*
 * ═════════════════════════════════════════════════════════════════════════════════════════
 *                    METE HOCA QWILINO ADVANCED ADDRESS CHANGER
 * ═════════════════════════════════════════════════════════════════════════════════════════
 * Description: 
 * This tool scans the I2C bus (Wire and Wire1) to find a connected Mete Hoca Qwilino 
 * module and allows the user to change its 7-bit I2C address via the Serial Monitor.
 *
 * NOTE FOR ARDUINO MODULINO USERS:
 * This script is specifically designed for original Mete Hoca Qwilino modules. 
 * DO NOT use this for Modulino modules. Please use the dedicated 
 * "Modulino Address Changer" for those devices to ensure compatibility.
 *
 * Instructions:
 * 1. Connect ONLY ONE Qwilino module to your Arduino (Uno R4 WiFi, etc.).
 * 2. Open the Serial Monitor and set the Baud Rate to 115200.
 * 3. Select "Both NL & CR" or "Newline" in the Serial Monitor settings.
 * 4. The script will identify the device. Enter the new HEX address (e.g., 2B).
 * 5. After the success message, power cycle the module to apply changes.
 * ═════════════════════════════════════════════════════════════════════════════════════════
 */

#include <Wire.h>

#if defined(WIRE_INTERFACES_COUNT) && (WIRE_INTERFACES_COUNT > 1)
  #define HAS_WIRE1
#elif defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_STM32) || defined(CORE_TEENSY) || defined(ARDUINO_SAM_DUE) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_UNO_Q)
  #define HAS_WIRE1
#endif

struct QwilinoLockedDevice {
  uint8_t     address;
  const char* name;
};

const QwilinoLockedDevice lockedDevices[] = {
  {0x48, "Qwilino Potentiometer"},
  {0x49, "Qwilino Temp"},
  {0x50, "Qwilino EEPROM"},
  {0x51, "Qwilino Clock"},
  {0x3D, "Qwilino OLED"}
};

struct QwilinoDevice {
  uint8_t deviceID;
  uint8_t defaultAddress;
  const char* expectedName;
};

const QwilinoDevice qwilinoCatalog[] = {
  {0x11, 0x0B, "Qwilino Potentiometer"},
  {0x12, 0x0C, "Qwilino Slider"},
  {0x13, 0x0D, "Qwilino Joystick"},
  {0x14, 0x0E, "Qwilino Light"},
  {0x21, 0x0F, "Qwilino Button"},
  {0x31, 0x2B, "Qwilino Buzzer"},
  {0x32, 0x2C, "Qwilino Relay"},
  {0x33, 0x2D, "Qwilino RGB"},
  {0x34, 0x2E, "Qwilino Motor"}
};

uint8_t foundAddress = 0;
uint8_t foundDeviceID = 0xFF;
String  foundDeviceName = "Unknown/Non-Qwilino Device"; 
uint8_t targetDefaultAddress = 0xFF;
TwoWire* foundBus = nullptr;

uint8_t readQwilinoID(TwoWire *bus, uint8_t address) {
  bus->beginTransmission(address);
  bus->write(0x00);
  if (bus->endTransmission() == 0) {
    bus->requestFrom(address, (uint8_t)1);
    if (bus->available()) return bus->read();
  }
  return 0xFF;
}

String readQwilinoName(TwoWire *bus, uint8_t address) {
  bus->beginTransmission(address);
  bus->write(0xEE);
  if (bus->endTransmission() == 0) {
    bus->requestFrom(address, (uint8_t)32);
    String name = "";
    while (bus->available()) {
      char c = bus->read();
      if (c == 0xFF || c == '\0') break;
      name += c;
    }
    name.trim();
    if (name.length() == 0) return "Unknown Device";
    return name;
  }
  return "Error Reading Name";
}

bool changeQwilinoAddress(TwoWire *bus, uint8_t currentAddress, uint8_t newAddress) {
  uint8_t data[48] = { 'C', 'F', (uint8_t)(newAddress * 2) };
  memset(data + 3, 0, sizeof(data) - 3);
  
  bus->beginTransmission(currentAddress);
  bus->write(data, sizeof(data));
  bus->endTransmission();
  
  Serial.print(F("Rebooting device securely... "));

  unsigned long startTime = millis();
  byte verifyError = 4; 
  
  while (millis() - startTime < 1000) {
    bus->beginTransmission(newAddress);
    verifyError = bus->endTransmission();
    if (verifyError == 0) break;
    delay(20); 
  }

  Serial.println(F("Done."));

  if (verifyError == 0) {
    Serial.print(F("SUCCESS! Module is now responding at new address: 0x"));
    if(newAddress < 16) Serial.print(F("0"));
    Serial.println(newAddress, HEX);
    return true;
  } else {
    Serial.print(F("ERROR! Module did not switch. Error code: "));
    Serial.println(verifyError);
    return false;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(500);
  Wire.begin();
  #ifdef HAS_WIRE1
  Wire1.begin();
  #endif
  
  uint8_t deviceCount = 0;

  for (uint8_t i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      foundAddress = i;
      foundBus = &Wire;
      deviceCount++;
      delay(2); 
    }
  }

  #ifdef HAS_WIRE1
  for (uint8_t i = 8; i < 120; i++) {
    Wire1.beginTransmission(i);
    if (Wire1.endTransmission() == 0) {
      foundAddress = i;
      foundBus = &Wire1;
      deviceCount++;
      delay(2); 
    }
  }
  #endif

  if (deviceCount == 0) {
    Serial.println(F("\nERROR: No connected device found!"));
    Serial.println(F("Check your Qwiic connection and reset the board."));
    while (1); 
  } else if (deviceCount > 1) {
    Serial.println(F("\nERROR: MORE THAN ONE device found across all I2C buses!"));
    Serial.println(F("Process halted to prevent accidental address overwrites."));
    Serial.println(F("Leave ONLY the module you want to change and reset the board."));
    while (1); 
  }

  Serial.println(F("\n══════════ METE HOCA QWILINO ADVANCED ADDRESS CHANGER ══════════"));
  Serial.println(F("INFO: Only applicable to the Qwilino devices."));
  Serial.println(F("Use 'Modulino Address Changer' for Arduino Modulino devices."));
  Serial.println(F("Addresses of OLED, Clock, Temp and EEPROM CANNOT BE CHANGED!"));
  Serial.println(F(">>> Please ensure ONLY ONE module is connected <<<"));
  Serial.println(F("════════════════════════════════════════════════════════════════"));

  for (uint8_t i = 0; i < sizeof(lockedDevices) / sizeof(lockedDevices[0]); i++) {
    if (foundAddress == lockedDevices[i].address) {
      Serial.print(F("\nDevice Found    : 0x"));
      if (foundAddress < 16) Serial.print(F("0"));
      Serial.print(foundAddress, HEX);
      Serial.print(F(" @ "));
      if (foundBus == &Wire) Serial.println(F("Wire"));
      #ifdef HAS_WIRE1
      else if (foundBus == &Wire1) Serial.println(F("Wire1"));
      #endif
      Serial.print(F("Device Name     : "));
      Serial.println(lockedDevices[i].name);
      Serial.println(F("\n[PROCESS CANCELLED]: The address of this module cannot be changed!"));
      while (1);
    }
  }

  foundDeviceID = readQwilinoID(foundBus, foundAddress);
  foundDeviceName = readQwilinoName(foundBus, foundAddress);

  for (uint8_t i = 0; i < sizeof(qwilinoCatalog) / sizeof(qwilinoCatalog[0]); i++) {
    if (qwilinoCatalog[i].deviceID == foundDeviceID) {
      targetDefaultAddress = qwilinoCatalog[i].defaultAddress;
      break;
    }
  }

  Serial.print(F("\nBus Port        : "));
  if (foundBus == &Wire) Serial.println(F("Wire"));
  #ifdef HAS_WIRE1
  else if (foundBus == &Wire1) Serial.println(F("Wire1"));
  #endif

  Serial.print(F("Current Address : 0x"));
  if (foundAddress < 16) Serial.print(F("0"));
  Serial.println(foundAddress, HEX);

  Serial.print(F("Device ID       : 0x"));
  if (foundDeviceID < 16) Serial.print(F("0"));
  Serial.println(foundDeviceID, HEX);

  Serial.print(F("Device Name     : "));
  Serial.println(foundDeviceName);

  if (targetDefaultAddress != 0xFF) {
    Serial.print(F("Factory Default : 0x"));
    if (targetDefaultAddress < 16) Serial.print(F("0"));
    Serial.println(targetDefaultAddress, HEX);
  } else {
    Serial.println(F("Factory Default : Unknown (Not in catalog)"));
  }

  Serial.println(F("\nWrite the new I2C address via the Serial Monitor."));
  Serial.println(F("NOTE: Valid standard I2C addresses are between 08 and 77."));
  
  if (targetDefaultAddress != 0xFF && targetDefaultAddress != foundAddress) {
    Serial.println(F("TIP: To revert to factory default, simply enter 'D'"));
  }
  Serial.println(F("Enter a 2-digit HEX value (e.g., 2A, 0B) or 'D':"));
}

void loop() {
  if (Serial.available() > 0 && foundAddress != 0 && foundBus != nullptr) {
    
    char buf[10];
    size_t len = Serial.readBytesUntil('\n', buf, sizeof(buf) - 1);
    buf[len] = '\0'; 

    if (len > 0 && buf[0] != '\r') {
      
      uint8_t newAddr = 0;

      if (buf[0] == 'D' || buf[0] == 'd') {
        if (targetDefaultAddress != 0xFF) {
          newAddr = targetDefaultAddress;
          Serial.println(F("\n[Shortcut] Loading Factory Default Address..."));
        } else {
          Serial.println(F("\nERROR: Factory default is unknown for this device. Please enter a HEX value manually."));
          return;
        }
      } else {
        newAddr = (uint8_t) strtol(buf, NULL, 16);
      }

      if (newAddr >= 0x08 && newAddr <= 0x77) {
        Serial.print(F("\nExecuting Address Swap... [0x"));
        if(foundAddress < 16) Serial.print(F("0"));
        Serial.print(foundAddress, HEX);
        Serial.print(F("] -> [0x"));
        if(newAddr < 16) Serial.print(F("0"));
        Serial.print(newAddr, HEX);
        Serial.println(F("]"));
        Serial.println(F("Please wait..."));
        
        if (changeQwilinoAddress(foundBus, foundAddress, newAddr)) {
          foundAddress = 0; 
          Serial.println(F("\nReady. You can now use the module with its new address."));
        }
        
      } else {
        Serial.println(F("\nInvalid input! Please enter a valid HEX value between 08 and 77, or 'D'."));
      }
    }
  }
}