#ifndef QWILINO_PIXELS_H
#define QWILINO_PIXELS_H

#include <Arduino.h>
#include <Wire.h>

#define QWILINO_PIXELS_ADDR 0x36

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_PIXELS_DEFAULT_WIRE Wire1
#else
  #define QWILINO_PIXELS_DEFAULT_WIRE Wire
#endif

struct QwilinoColor {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  
  QwilinoColor(uint8_t red, uint8_t green, uint8_t blue) 
    : r(red), g(green), b(blue) {}
  QwilinoColor() : r(0), g(0), b(0) {}
};

extern const QwilinoColor RED;
extern const QwilinoColor GREEN;
extern const QwilinoColor BLUE;
extern const QwilinoColor YELLOW;
extern const QwilinoColor CYAN;
extern const QwilinoColor MAGENTA;
extern const QwilinoColor WHITE;
extern const QwilinoColor BLACK; 

class QwilinoPixels {
public:
  QwilinoPixels(uint8_t address = QWILINO_PIXELS_ADDR);

  bool begin(TwoWire *wire = &QWILINO_PIXELS_DEFAULT_WIRE);

  void set(uint8_t index, QwilinoColor color, uint8_t brightness = 255);
  void set(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness = 255);

  void clear();
  void show();

private:
  uint8_t _address;
  TwoWire *_wire;
  
  struct LEDData {
    uint8_t r, g, b, w;
  };
  
  LEDData _leds[8];
};

#endif