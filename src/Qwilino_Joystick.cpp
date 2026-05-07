#include "Qwilino_Joystick.h"

Qwilino_Joystick::Qwilino_Joystick(uint8_t address) {
  _address = address;
}

bool Qwilino_Joystick::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;
  _i2cPort->begin();
  _i2cPort->beginTransmission(_address);
  return (_i2cPort->endTransmission() == 0);
}

int16_t Qwilino_Joystick::getX() {
  return readRegister16(0x01);
}

int16_t Qwilino_Joystick::getY() {
  return readRegister16(0x03);
}

bool Qwilino_Joystick::getButton() {
  return (readRegister8(0x05) == 0);
}

int16_t Qwilino_Joystick::readRegister16(uint8_t reg) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  _i2cPort->endTransmission(false);
  
  // DÜZELTİLEN SATIR
  _i2cPort->requestFrom((uint8_t)_address, (size_t)2);
  
  if (_i2cPort->available() >= 2) {
    uint8_t lsb = _i2cPort->read();
    uint8_t msb = _i2cPort->read();
    return (int16_t)((msb << 8) | lsb);
  }
  return 0;
}

uint8_t Qwilino_Joystick::readRegister8(uint8_t reg) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  _i2cPort->endTransmission(false);
  
  // DÜZELTİLEN SATIR
  _i2cPort->requestFrom((uint8_t)_address, (size_t)1);
  
  if (_i2cPort->available()) {
    return _i2cPort->read();
  }
  return 1;
}