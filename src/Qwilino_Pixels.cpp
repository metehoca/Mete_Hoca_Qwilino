#include "Qwilino_Pixels.h"

const QwilinoColor RED(255, 0, 0);
const QwilinoColor GREEN(0, 255, 0);
const QwilinoColor BLUE(0, 0, 255);
const QwilinoColor YELLOW(255, 255, 0);
const QwilinoColor CYAN(0, 255, 255);
const QwilinoColor MAGENTA(255, 0, 255);
const QwilinoColor WHITE(255, 255, 255);
const QwilinoColor BLACK(0, 0, 0);

QwilinoPixels::QwilinoPixels(uint8_t address) {
  _address = address;
  _wire = &QWILINO_PIXELS_DEFAULT_WIRE;
  clear();
}

bool QwilinoPixels::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  
  _wire->beginTransmission(_address);
  uint8_t error = _wire->endTransmission();
  
  if (error == 0) {
    show(); 
    return true;
  }
  return false;
}

void QwilinoPixels::set(uint8_t index, QwilinoColor color, uint8_t brightness) {
  set(index, color.r, color.g, color.b, brightness);
}

void QwilinoPixels::set(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
  if (index >= 8) return; 
  
  _leds[index].r = r;
  _leds[index].g = g;
  _leds[index].b = b;
  _leds[index].w = brightness;
}

void QwilinoPixels::clear() {
  for (int i = 0; i < 8; i++) {
    set(i, 0, 0, 0, 0);
  }
}

void QwilinoPixels::show() {
  uint8_t buffer[32];
  
  for (int i = 0; i < 8; i++) {
    buffer[i * 4 + 0] = 0x80 | (_leds[i].w >> 3); 
    buffer[i * 4 + 1] = _leds[i].b;
    buffer[i * 4 + 2] = _leds[i].g;
    buffer[i * 4 + 3] = _leds[i].r;
  }
  
  _wire->beginTransmission(_address);
  for (int i = 0; i < 32; i++) {
    _wire->write(buffer[i]);
  }
  _wire->endTransmission();
}