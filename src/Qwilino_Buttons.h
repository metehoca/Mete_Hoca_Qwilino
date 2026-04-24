#ifndef QWILINO_BUTTONS_H
#define QWILINO_BUTTONS_H

#include <Arduino.h>
#include <Wire.h>

#define QWILINO_BUTTONS_ADDR 0x3E

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_BUTTONS_DEFAULT_WIRE Wire1
#else
  #define QWILINO_BUTTONS_DEFAULT_WIRE Wire
#endif

class QwilinoButtons {
public:
  QwilinoButtons(uint8_t address = QWILINO_BUTTONS_ADDR);

  bool begin(TwoWire *wire = &QWILINO_BUTTONS_DEFAULT_WIRE);

  bool update();

  bool isPressed(int index);
  bool isPressed(char button);

  void setLeds(bool a, bool b, bool c);

private:
  uint8_t _address;
  TwoWire *_wire;
  bool _lastStatus[3];
  
  int charToIndex(char c);
};

#endif