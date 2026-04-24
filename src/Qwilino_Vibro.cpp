#include "Qwilino_Vibro.h"

Qwilino_Vibro::Qwilino_Vibro(uint8_t address) {
  _address = address;
}

bool Qwilino_Vibro::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;
  _i2cPort->begin();
  _i2cPort->beginTransmission(_address);
  return (_i2cPort->endTransmission() == 0);
}

void Qwilino_Vibro::on(uint16_t duration_ms) {
  writeRegister(0x01, 0x01);
  if (duration_ms > 0) {
    delay(duration_ms);
    off();
  }
}

void Qwilino_Vibro::off() {
  writeRegister(0x01, 0x00);
}

void Qwilino_Vibro::setIntensity(uint8_t intensity) {
  writeRegister(0x02, intensity);
}

void Qwilino_Vibro::writeRegister(uint8_t reg, uint8_t value) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  _i2cPort->write(value);
  _i2cPort->endTransmission();
}