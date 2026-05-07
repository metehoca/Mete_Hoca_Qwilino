#ifndef QWILINO_EEPROM_H
#define QWILINO_EEPROM_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_EEPROM_DEFAULT_WIRE Wire1
#else
  #define QWILINO_EEPROM_DEFAULT_WIRE Wire
#endif

#ifdef EEPROM_SIZE
  #undef EEPROM_SIZE
#endif

class QwilinoEEPROM {
public:
  static constexpr uint8_t DEFAULT_ADDRESS = 0x50;
  static constexpr uint32_t EEPROM_SIZE = 32768;
  static constexpr uint8_t PAGE_SIZE = 64;

  QwilinoEEPROM(uint8_t address = DEFAULT_ADDRESS);
  
  bool begin(TwoWire *wire = &QWILINO_EEPROM_DEFAULT_WIRE);
  
  bool updateByte(uint16_t address, uint8_t data);
  uint8_t readByte(uint16_t address);
  
  template <typename T> const T &put(uint16_t address, const T &t) {
    if (address + sizeof(T) > EEPROM_SIZE) return t;
    const uint8_t *ptr = (const uint8_t*)&t;
    for (uint16_t i = 0; i < sizeof(T); i++) {
      updateByte(address + i, ptr[i]);
    }
    return t;
  }

  template <typename T> void get(uint16_t address, T &t) {
    if (address + sizeof(T) > EEPROM_SIZE) return;
    uint8_t *ptr = (uint8_t*)&t;
    for (uint16_t i = 0; i < sizeof(T); i++) {
      ptr[i] = readByte(address + i);
    }
  }

private:
  uint8_t _address;
  TwoWire *_wire;
  void _waitForWriteCycle();
};

#endif