#ifndef QWILINO_VIBRO_H
#define QWILINO_VIBRO_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_VIBRO_DEFAULT_WIRE Wire1
#else
  #define QWILINO_VIBRO_DEFAULT_WIRE Wire
#endif

class Qwilino_Vibro {
  public:
    Qwilino_Vibro(uint8_t address = 0x38);
    bool begin(TwoWire &wirePort = QWILINO_VIBRO_DEFAULT_WIRE);
    void on(uint16_t duration_ms = 0);
    void off();
    void setIntensity(uint8_t intensity);

  private:
    uint8_t _address;
    TwoWire *_i2cPort;
    void writeRegister(uint8_t reg, uint8_t value);
};

#endif