#include "Qwilino_Buttons.h"

QwilinoButtons::QwilinoButtons(uint8_t address) {
  _address = address;
  // Baþlangýç deðerini makrodan alýyoruz
  _wire = &QWILINO_BUTTONS_DEFAULT_WIRE;
  _lastStatus[0] = false;
  _lastStatus[1] = false;
  _lastStatus[2] = false;
}

bool QwilinoButtons::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

bool QwilinoButtons::update() {
  uint8_t quantity = _wire->requestFrom((uint8_t)_address, (size_t)4);

  if (quantity < 4) {
    return false;
  }

  _wire->read(); // Ýlk byte'ý atla (Dummy/Status)

  uint8_t newStatus[3];
  newStatus[0] = _wire->read();
  newStatus[1] = _wire->read();
  newStatus[2] = _wire->read();

  bool changed = (newStatus[0] != _lastStatus[0]) || 
                 (newStatus[1] != _lastStatus[1]) || 
                 (newStatus[2] != _lastStatus[2]);

  _lastStatus[0] = (newStatus[0] != 0);
  _lastStatus[1] = (newStatus[1] != 0);
  _lastStatus[2] = (newStatus[2] != 0);

  return changed;
}

bool QwilinoButtons::isPressed(int index) {
  if (index < 0 || index > 2) return false;
  return _lastStatus[index];
}

bool QwilinoButtons::isPressed(char button) {
  return isPressed(charToIndex(button));
}

void QwilinoButtons::setLeds(bool a, bool b, bool c) {
  _wire->beginTransmission(_address);
  _wire->write((uint8_t)a);
  _wire->write((uint8_t)b);
  _wire->write((uint8_t)c);
  _wire->endTransmission();
}

int QwilinoButtons::charToIndex(char c) {
  switch (c) {
    case 'A': case 'a': return 0;
    case 'B': case 'b': return 1;
    case 'C': case 'c': return 2;
    default: return -1;
  }
}