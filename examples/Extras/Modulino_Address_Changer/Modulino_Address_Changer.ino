/*
 * ═════════════════════════════════════════════════════════════════════════════════════════
 *                    METE HOCA MODULINO ADVANCED ADDRESS CHANGER
 * ═════════════════════════════════════════════════════════════════════════════════════════
 * Description: 
 * This tool scans the I2C bus (Wire and Wire1) to find a connected Arduino Modulino 
 * module and allows the user to change its 7-bit I2C address via the Serial Monitor.
 *
 * NOTE FOR QWILINO USERS:
 * This script is specifically designed for original Arduino Modulino modules. 
 * DO NOT use this for Qwilino modules. Please use the dedicated 
 * "Qwilino Address Changer" for those devices to ensure compatibility.
 *
 * Instructions:
 * 1. Connect ONLY ONE Modulino module to your Arduino (Uno R4 WiFi, etc.).
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

struct I2CDevice {
  uint8_t     address;
  const char* name;
};

const I2CDevice knownDevices[] = {
  {0x3E, "Modulino Buttons"},
  {0x1E, "Modulino Buzzer"},
  {0x20, "Modulino Joystick"},
  {0x3A, "Modulino Knob"},
  {0x15, "Modulino Latch Relay"},
  {0x53, "Modulino Light"},
  {0x19, "Modulino LED Matrix"},
  {0x36, "Modulino Pixels"},
  {0x44, "Modulino Thermo"},
  {0x1D, "Modulino Vibro"},
  {0x29, "Modulino Distance"},
  {0x6A, "Modulino Movement"},
  {0x6B, "Modulino Movement(Alt)"}
};

struct HardwareIdEntry {
  uint8_t     id;
  uint8_t     defaultAddr;
  const char* name;
};

const HardwareIdEntry hardwareIds[] = {
  {0x7C, 0x3E, "Modulino Buttons"},
  {0x74, 0x3A, "Modulino Knob"},
  {0x76, 0x3A, "Modulino Knob2"},
  {0x3C, 0x1E, "Modulino Buzzer"},
  {0x40, 0x20, "Modulino Joystick"},
  {0x2A, 0x15, "Modulino Latch Relay"},
  {0x3A, 0x1D, "Modulino Vibro"},
  {0x32, 0x19, "Modulino LED Matrix"},
  {0x6C, 0x36, "Modulino Pixels"}
};

uint8_t     foundAddress    = 0;
const char* foundDeviceName = "Unknown Device";
TwoWire*    foundBus        = nullptr;

bool    waitingForConfirmation = false;
uint8_t pendingNewAddr         = 0;

bool    offerDefaultRestore = false;
uint8_t defaultRestoreAddr  = 0;

const char* findKnownDeviceName(uint8_t addr) {
  for (uint8_t i = 0; i < sizeof(knownDevices) / sizeof(knownDevices[0]); i++) {
    if (knownDevices[i].address == addr) return knownDevices[i].name;
  }
  return nullptr;
}

const HardwareIdEntry* findHardwareEntry(uint8_t id) {
  for (uint8_t i = 0; i < sizeof(hardwareIds) / sizeof(hardwareIds[0]); i++) {
    if (hardwareIds[i].id == id) return &hardwareIds[i];
  }
  return nullptr;
}

uint8_t readHardwareId(TwoWire* bus, uint8_t address) {
  bus->beginTransmission(address);
  bus->write(0x00);
  if (bus->endTransmission(false) != 0) return 0xFF;
  if (bus->requestFrom(address, (uint8_t)1) != 1) return 0xFF;
  return bus->read();
}

bool changeModulinoAddress(TwoWire* bus, uint8_t currentAddress, uint8_t newAddress) {
  uint8_t data[48] = { 'C', 'F', (uint8_t)(newAddress * 2) };
  memset(data + 3, 0, sizeof(data) - 3);
  bus->beginTransmission(currentAddress);
  bus->write(data, sizeof(data));
  bus->endTransmission();
  delay(100);
  bus->beginTransmission(newAddress);
  byte verifyError = bus->endTransmission();
  if (verifyError == 0) {
    Serial.print(F("Success! Module is now responding at new address: 0x"));
    if (newAddress < 16) Serial.print(F("0"));
    Serial.println(newAddress, HEX);
    return true;
  } else {
    Serial.print(F("Error! Module did not switch to the new address. Error code: "));
    Serial.println(verifyError);
    return false;
  }
}

void printDeviceInfo(uint8_t address, TwoWire* bus) {
  const char*             addrName = findKnownDeviceName(address);
  uint8_t                 hwId     = readHardwareId(bus, address);
  const HardwareIdEntry*  hwEntry  = findHardwareEntry(hwId);

  Serial.print(F("  I2C Address : 0x"));
  if (address < 16) Serial.print(F("0"));
  Serial.println(address, HEX);

  Serial.print(F("  Address Map : "));
  if (addrName) {
    Serial.println(addrName);
  } else {
    Serial.println(F("Unknown (custom/modified address)"));
  }

  Serial.print(F("  Hardware ID : "));
  if (hwId != 0xFF) {
    Serial.print(F("0x"));
    if (hwId < 16) Serial.print(F("0"));
    Serial.print(hwId, HEX);
    Serial.print(F("  ->  "));
    if (hwEntry) {
      Serial.print(hwEntry->name);
      Serial.print(F("  (Default I2C: 0x"));
      if (hwEntry->defaultAddr < 16) Serial.print(F("0"));
      Serial.print(hwEntry->defaultAddr, HEX);
      Serial.println(F(")"));
    } else {
      Serial.println(F("Unrecognised MCU module"));
    }
  } else {
    Serial.println(F("N/A  (no MCU or read error)"));
  }

  if      (hwEntry)  foundDeviceName = hwEntry->name;
  else if (addrName) foundDeviceName = addrName;
  else               foundDeviceName = "Unknown Device";

  if (hwEntry && address != hwEntry->defaultAddr) {
    offerDefaultRestore = true;
    defaultRestoreAddr  = hwEntry->defaultAddr;
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
      foundBus     = &Wire;
      deviceCount++;
      delay(1);
    }
  }

  #ifdef HAS_WIRE1
  for (uint8_t i = 8; i < 120; i++) {
    Wire1.beginTransmission(i);
    if (Wire1.endTransmission() == 0) {
      foundAddress = i;
      foundBus     = &Wire1;
      deviceCount++;
      delay(1);
    }
  }
  #endif

  if (deviceCount == 0) {
    Serial.println(F("\nERROR: No connected device found!"));
    Serial.println(F("Check connections and restart the system."));
    while (1);
  } else if (deviceCount > 1) {
    Serial.println(F("\nERROR: MORE THAN ONE device found across all I2C buses!"));
    Serial.println(F("Process halted for safety."));
    Serial.println(F("Leave only the module you want to change and reset."));
    while (1);
  }

  Serial.println(F("══════════ METE HOCA MODULINO ADVANCED ADDRESS CHANGER ══════════"));
  Serial.println(F("INFO: Only applicable to the Arduino's Modulino devices."));
  Serial.println(F("Use 'Qwilino Address Changer' for METE HOCA Qwilino devices."));
  Serial.println(F("Addresses of Distance, Movement, Thermo and Light CANNOT BE CHANGED!"));
  Serial.println(F(">>> Please ensure ONLY ONE module is connected <<<"));
  Serial.println(F("═════════════════════════════════════════════════════════════════"));

  Serial.print(F("\nDevice found on bus : "));
  #ifdef HAS_WIRE1
  Serial.println(foundBus == &Wire ? F("Wire") : F("Wire1"));
  #else
  Serial.println(F("Wire"));
  #endif

  printDeviceInfo(foundAddress, foundBus);

  if (strcmp(foundDeviceName, "Modulino Thermo")   == 0 ||
      strcmp(foundDeviceName, "Modulino Light")    == 0 ||
      strcmp(foundDeviceName, "Modulino Distance") == 0 ||
      strcmp(foundDeviceName, "Modulino Movement") == 0) {
    Serial.println(F("\n[PROCESS CANCELLED]: The address of this module cannot be changed!"));
    while (1);
  }

  
  Serial.println(F("\nNOTE: Valid standard I2C addresses are between 08 and 77."));
  Serial.println(F("Enter only a 2-digit HEX value (e.g., 3A, 4C, etc.)\n"));

  Serial.println(F("Write the new I2C address via the Serial Monitor."));
  if (offerDefaultRestore) {
    Serial.print(F("Or simply enter 'D' to restore the default address (0x"));
    if (defaultRestoreAddr < 16) Serial.print(F("0"));
    Serial.print(defaultRestoreAddr, HEX);
    Serial.println(F(")."));
  }
}

void loop() {
  if (Serial.available() > 0 && foundAddress != 0 && foundBus != nullptr) {

    char buf[10];
    size_t len = Serial.readBytesUntil('\n', buf, sizeof(buf) - 1);
    buf[len] = '\0';

    if (len == 0 || buf[0] == '\r') return;

    if (waitingForConfirmation) {

      char trimmed[10];
      uint8_t t = 0;
      for (uint8_t i = 0; i < len && t < sizeof(trimmed) - 1; i++) {
        if (buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\t') {
          trimmed[t++] = buf[i];
        }
      }
      trimmed[t] = '\0';

      if (strcasecmp(trimmed, "Y") == 0 || strcasecmp(trimmed, "YES") == 0) {
        Serial.print(F("\nConfirmed. Changing Address... Old: 0x"));
        if (foundAddress < 16) Serial.print(F("0"));
        Serial.print(foundAddress, HEX);
        Serial.print(F(" -> New: 0x"));
        if (pendingNewAddr < 16) Serial.print(F("0"));
        Serial.println(pendingNewAddr, HEX);

        changeModulinoAddress(foundBus, foundAddress, pendingNewAddr);

        foundAddress           = 0;
        waitingForConfirmation = false;
        pendingNewAddr         = 0;
        Serial.println(F("\nPlease power cycle (disconnect and reconnect power) the device for the changes to take effect."));

      } else if (strcasecmp(trimmed, "N") == 0 || strcasecmp(trimmed, "NO") == 0) {
        Serial.println(F("\n[CANCELLED] Address change aborted by user."));
        Serial.println(F("Enter a new HEX address to try again."));
        waitingForConfirmation = false;
        pendingNewAddr         = 0;

      } else {
        Serial.println(F("Invalid input! Please type Y (yes) or N (no)."));
      }

      return;
    }

    char trimmedBuf[10];
    uint8_t t = 0;
    for (uint8_t i = 0; i < len && t < sizeof(trimmedBuf) - 1; i++) {
      if (buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\t') {
        trimmedBuf[t++] = buf[i];
      }
    }
    trimmedBuf[t] = '\0';

    if (offerDefaultRestore && strcasecmp(trimmedBuf, "D") == 0) {
      Serial.print(F("\nRestoring default address... Current: 0x"));
      if (foundAddress < 16) Serial.print(F("0"));
      Serial.print(foundAddress, HEX);
      Serial.print(F(" -> Default: 0x"));
      if (defaultRestoreAddr < 16) Serial.print(F("0"));
      Serial.println(defaultRestoreAddr, HEX);

      changeModulinoAddress(foundBus, foundAddress, defaultRestoreAddr);

      foundAddress        = 0;
      offerDefaultRestore = false;
      Serial.println(F("\nPlease power cycle (disconnect and reconnect power) the device for the changes to take effect."));
      return;
    }

    uint8_t newAddr = (uint8_t) strtol(buf, NULL, 16);

    if (newAddr >= 0x08 && newAddr <= 0x77) {

      const char* conflictName = findKnownDeviceName(newAddr);

      if (conflictName != nullptr) {
        Serial.print(F("\n[WARNING] The address 0x"));
        if (newAddr < 16) Serial.print(F("0"));
        Serial.print(newAddr, HEX);
        Serial.print(F(" is the default address of '"));
        Serial.print(conflictName);
        Serial.println(F("'."));
        Serial.println(F("Setting this address may cause conflicts if that module is"));
        Serial.println(F("ever connected to the same bus."));
        Serial.print(F("Are you sure you want to change to 0x"));
        if (newAddr < 16) Serial.print(F("0"));
        Serial.print(newAddr, HEX);
        Serial.println(F("? (Y/N)"));

        pendingNewAddr         = newAddr;
        waitingForConfirmation = true;

      } else {
        Serial.print(F("\nChanging Address... Old Address: 0x"));
        if (foundAddress < 16) Serial.print(F("0"));
        Serial.print(foundAddress, HEX);
        Serial.print(F(" -> New Target: 0x"));
        if (newAddr < 16) Serial.print(F("0"));
        Serial.println(newAddr, HEX);

        changeModulinoAddress(foundBus, foundAddress, newAddr);

        foundAddress = 0;
        Serial.println(F("\nPlease power cycle (disconnect and reconnect power) the device for the changes to take effect."));
      }

    } else {
      Serial.println(F("\nInvalid input! Please enter a HEX value between 08 and 77."));
    }
  }
}
