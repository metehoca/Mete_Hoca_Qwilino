#include "Qwilino_Knob.h"

QwilinoKnob::QwilinoKnob(uint8_t address) {
  _address = address;
  _wire = &QWILINO_KNOB_DEFAULT_WIRE;
  _position = 0;
  _lastPosition = 0;
  _buttonState = false;
  _lastButtonState = false;
  _lastReadTime = 0;
}

bool QwilinoKnob::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

void QwilinoKnob::update() {
  uint8_t received = _wire->requestFrom(_address, (uint8_t)4);

  if (received == 4) {
    _wire->read();

    uint8_t lsb = _wire->read();
    uint8_t msb = _wire->read();
    uint8_t btn = _wire->read();

    _lastPosition = _position; 
    _position = (int16_t)(lsb | (msb << 8));
    
    _lastButtonState = _buttonState;
    _buttonState = (btn != 0);
  }
}

int16_t QwilinoKnob::getPosition() {
  return _position;
}

void QwilinoKnob::setPosition(int16_t value) {
  _wire->beginTransmission(_address);
  
  _wire->write((uint8_t)(value & 0xFF));        
  _wire->write((uint8_t)((value >> 8) & 0xFF)); 
  _wire->write((uint8_t)0); 
  _wire->write((uint8_t)0); 
  
  _wire->endTransmission();
  
  _position = value;
  _lastPosition = value;
}

bool QwilinoKnob::isPressed() {
  return _buttonState;
}

int QwilinoKnob::getDirection() {
  if (_position > _lastPosition) return 1;
  if (_position < _lastPosition) return -1;
  return 0;
}