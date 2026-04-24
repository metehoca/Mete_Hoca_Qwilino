#ifndef QWILINO_LIGHT_H
#define QWILINO_LIGHT_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_LIGHT_DEFAULT_WIRE Wire1
#else
  #define QWILINO_LIGHT_DEFAULT_WIRE Wire
#endif

class Qwilino_Light {
  public:
    Qwilino_Light(uint8_t address = 0x53);
    bool begin(TwoWire &wirePort = QWILINO_LIGHT_DEFAULT_WIRE);
    uint32_t getAmbient();
    uint32_t getRed();
    uint32_t getGreen();
    uint32_t getBlue();
    uint32_t getInfrared();

  private:
    uint8_t _address;
    TwoWire *_i2cPort;
    void writeRegister(uint8_t reg, uint8_t value);
    uint32_t readRegister24(uint8_t reg);
};

#endif