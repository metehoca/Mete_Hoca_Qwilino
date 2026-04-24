#ifndef QWILINO_RELAY_H
#define QWILINO_RELAY_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_RELAY_DEFAULT_WIRE Wire1
#else
  #define QWILINO_RELAY_DEFAULT_WIRE Wire
#endif

class Qwilino_Relay {
  public:
    Qwilino_Relay(uint8_t address = 0x40);
    bool begin(TwoWire &wirePort = QWILINO_RELAY_DEFAULT_WIRE);
    void set();
    void reset();
    void toggle();
    bool getState();

  private:
    uint8_t _address;
    TwoWire *_i2cPort;
    bool _currentState;
    void writeCommand(uint8_t command);
};

#endif