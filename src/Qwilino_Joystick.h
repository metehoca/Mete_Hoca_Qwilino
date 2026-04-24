#ifndef QWILINO_JOYSTICK_H
#define QWILINO_JOYSTICK_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_JOYSTICK_DEFAULT_WIRE Wire1
#else
  #define QWILINO_JOYSTICK_DEFAULT_WIRE Wire
#endif

class Qwilino_Joystick {
  public:
    Qwilino_Joystick(uint8_t address = 0x4A);
    bool begin(TwoWire &wirePort = QWILINO_JOYSTICK_DEFAULT_WIRE);
    int16_t getX();
    int16_t getY();
    bool getButton();

  private:
    uint8_t _address;
    TwoWire *_i2cPort;
    int16_t readRegister16(uint8_t reg);
    uint8_t readRegister8(uint8_t reg);
};

#endif