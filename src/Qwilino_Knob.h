#ifndef QWILINO_KNOB_H
#define QWILINO_KNOB_H

#include <Arduino.h>
#include <Wire.h>

#define QWILINO_KNOB_ADDR 0x3A

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_KNOB_DEFAULT_WIRE Wire1
#else
  #define QWILINO_KNOB_DEFAULT_WIRE Wire
#endif

class QwilinoKnob {
public:
  QwilinoKnob(uint8_t address = QWILINO_KNOB_ADDR);
  
  bool begin(TwoWire *wire = &QWILINO_KNOB_DEFAULT_WIRE);
  
  void update();
  
  int16_t getPosition();
  void setPosition(int16_t value);
  
  bool isPressed();
  int getDirection();

private:
  uint8_t _address;
  TwoWire *_wire;
  int16_t _position;
  int16_t _lastPosition;
  bool _buttonState;
  bool _lastButtonState;
  unsigned long _lastReadTime;
};

#endif