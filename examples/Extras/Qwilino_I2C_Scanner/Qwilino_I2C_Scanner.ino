/*
 * Qwilino Universal I2C Scanner
 * * A specialized I2C scanner designed for the Qwilino and Modulino ecosystem.
 * It automatically detects if the target board supports a secondary I2C 
 * interface (Wire1) and scans both interfaces seamlessly. Known Modulino 
 * and Qwilino devices are automatically identified by their default addresses.
 * * Supported Boards for Wire1 Auto-Detection:
 * - Arduino Uno R4 WiFi
 * - Arduino Nano R4
 * - Arduino Uno Q
 * - ESP32 Series
 * - RP2040 Based Boards
 * - STM32 Series, Teensy, Arduino Due
 * - Any board with WIRE_INTERFACES_COUNT > 1
 */

#include <Wire.h>

#if defined(WIRE_INTERFACES_COUNT) && (WIRE_INTERFACES_COUNT > 1)
  #define HAS_WIRE1
#elif defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_STM32) || defined(CORE_TEENSY) || defined(ARDUINO_SAM_DUE) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_UNO_Q)
  #define HAS_WIRE1
#endif

struct I2CDevice {
  uint8_t address;
  const char* name;
};

const I2CDevice knownDevices[] = {
  {0x3D, "Qwilino OLED"},
  {0x48, "Qwilino Potentiometer"},
  {0x50, "Qwilino EEPROM"},
  {0x51, "Qwilino Clock"},
  {0x49, "Qwilino Temp"},
  {0x3E, "Modulino Buttons"},
  {0x1E, "Modulino Buzzer"},
  {0x29, "Modulino Distance"},
  {0x20, "Modulino Joystick"},
  {0x3A, "Modulino Knob"},
  {0x15, "Modulino Latch Relay"},
  {0x53, "Modulino Light"},
  {0x19, "Modulino LED Matrix"},
  {0x6A, "Modulino Movement"},
  {0x6B, "Modulino Movement (Jumpered)"},
  {0x7E, "Modulino Movement (Auxiliary)"},
  {0x36, "Modulino Pixels"},
  {0x44, "Modulino Thermo"},
  {0x1D, "Modulino Vibro"}
};

const int numKnownDevices = sizeof(knownDevices) / sizeof(knownDevices[0]);

#define MAX_FOUND 30

struct FoundDevice {
  uint8_t address;
  const char* name;
  const char* port;
};

FoundDevice foundList[MAX_FOUND];
int foundCount = 0;

const char* getDeviceName(uint8_t address) {
  for (int i = 0; i < numKnownDevices; i++) {
    if (knownDevices[i].address == address) {
      return knownDevices[i].name;
    }
  }
  return "Unidentified Device";
}

void scanPort(TwoWire& wirePort, const char* portName) {
  byte error, address;
  for(address = 1; address < 127; address++) {
    wirePort.beginTransmission(address);
    error = wirePort.endTransmission();
    if (error == 0) {
      if (foundCount < MAX_FOUND) {
        foundList[foundCount].address = address;
        foundList[foundCount].name = getDeviceName(address);
        foundList[foundCount].port = portName;
        foundCount++;
      }
    }
    delayMicroseconds(10);
  }
}

int getDevicePriority(const char* name) {
  if (strncmp(name, "Qwilino", 7) == 0) return 1;
  if (strcmp(name, "Unidentified Device") == 0) return 3;
  return 2;
}

void sortResults() {
  for (int i = 0; i < foundCount - 1; i++) {
    for (int j = 0; j < foundCount - i - 1; j++) {
      bool swap = false;
      int portCmp = strcmp(foundList[j].port, foundList[j+1].port);
      if (portCmp > 0) {
        swap = true;
      } else if (portCmp == 0) {
        int prio1 = getDevicePriority(foundList[j].name);
        int prio2 = getDevicePriority(foundList[j+1].name);
        if (prio1 > prio2) {
          swap = true;
        } else if (prio1 == prio2) {
          if (foundList[j].address > foundList[j+1].address) {
            swap = true;
          }
        }
      }
      if (swap) {
        FoundDevice temp = foundList[j];
        foundList[j] = foundList[j+1];
        foundList[j+1] = temp;
      }
    }
  }
}

void printResults() {
  Serial.println("\n╔══════════ QWILINO I2C SCANNER ══════════╗");
  if (foundCount == 0) {
    Serial.println("  No I2C devices detected.");
  } else {
    sortResults();
    for (int i = 0; i < foundCount; i++) {
      Serial.print("  0x");
      if (foundList[i].address < 16) {
        Serial.print("0");
      }
      Serial.print(foundList[i].address, HEX);
      Serial.print(" @ ");
      Serial.print(foundList[i].port);
      if (strcmp(foundList[i].port, "Wire") == 0) {
        Serial.print(" ");
      }
      Serial.print(" -> ");
      Serial.println(foundList[i].name);
    }
  }
  Serial.println("╚═════════════════════════════════════════╝\n");
}

void setup() {
  while (!Serial && millis() < 3000);
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(100000);
  #ifdef HAS_WIRE1
  Wire1.begin();
  Wire1.setClock(100000);
  #endif
}

void loop() {
  foundCount = 0;
  scanPort(Wire, "Wire");
  #ifdef HAS_WIRE1
  scanPort(Wire1, "Wire1");
  #endif
  printResults();
  delay(5000);
}