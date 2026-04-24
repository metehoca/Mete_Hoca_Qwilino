#include "Qwilino_EEPROM.h"

QwilinoEEPROM::QwilinoEEPROM(uint8_t address) {
  _address = address;
  _wire = &QWILINO_EEPROM_DEFAULT_WIRE;
}

bool QwilinoEEPROM::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

bool QwilinoEEPROM::updateByte(uint16_t address, uint8_t data) {
  if (address >= EEPROM_SIZE) return false;
  
  uint8_t currentData = readByte(address);
  if (currentData == data) return true;
  
  _wire->beginTransmission(_address);
  _wire->write((int)(address >> 8));
  _wire->write((int)(address & 0xFF));
  _wire->write(data);
  
  if (_wire->endTransmission() != 0) return false;
  _waitForWriteCycle();
  
  return true;
}

uint8_t QwilinoEEPROM::readByte(uint16_t address) {
  if (address >= EEPROM_SIZE) return 0xFF;
  
  _wire->beginTransmission(_address);
  _wire->write((int)(address >> 8));
  _wire->write((int)(address & 0xFF));
  _wire->endTransmission();
  
  _wire->requestFrom(_address, (uint8_t)1);
  if (_wire->available()) {
    return _wire->read();
  }
  return 0xFF;
}

void QwilinoEEPROM::_waitForWriteCycle() {
  delay(5);
}