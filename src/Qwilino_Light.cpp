#include "Qwilino_Light.h"

Qwilino_Light::Qwilino_Light(uint8_t address) {
  _address = address;
}

bool Qwilino_Light::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;
  _i2cPort->begin();
  _i2cPort->beginTransmission(_address);
  if (_i2cPort->endTransmission() != 0) return false;
  
  writeRegister(0x00, 0x02);
  return true;
}

uint32_t Qwilino_Light::getAmbient() {
  return readRegister24(0x0A);
}

uint32_t Qwilino_Light::getRed() {
  return readRegister24(0x0D);
}

uint32_t Qwilino_Light::getGreen() {
  return readRegister24(0x10);
}

uint32_t Qwilino_Light::getBlue() {
  return readRegister24(0x13);
}

uint32_t Qwilino_Light::getInfrared() {
  return readRegister24(0x16);
}

void Qwilino_Light::writeRegister(uint8_t reg, uint8_t value) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  _i2cPort->write(value);
  _i2cPort->endTransmission();
}

uint32_t Qwilino_Light::readRegister24(uint8_t reg) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_address, (uint8_t)3);
  
  if (_i2cPort->available() >= 3) {
    uint32_t val = _i2cPort->read();
    val |= ((uint32_t)_i2cPort->read() << 8);
    val |= ((uint32_t)_i2cPort->read() << 16);
    return val;
  }
  return 0;
}