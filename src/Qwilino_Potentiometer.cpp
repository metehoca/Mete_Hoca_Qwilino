#include "Qwilino_Potentiometer.h"

#define ADS1015_REG_POINTER_CONVERT 0x00
#define ADS1015_REG_POINTER_CONFIG  0x01

Qwilino_Potentiometer::Qwilino_Potentiometer() {
  _address = 0x48;
  _gain = QWILINO_POTENTIOMETER_PGA_1;
  _wire = &QWILINO_POTENTIOMETER_DEFAULT_WIRE;
}

bool Qwilino_Potentiometer::begin(uint8_t address, TwoWire &wirePort) {
  _address = address;
  _wire = &wirePort;
  
  _wire->begin();
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

void Qwilino_Potentiometer::setGain(Qwilino_Potentiometer_Gain gain) {
  _gain = gain;
}

int16_t Qwilino_Potentiometer::read() {
  return read(QWILINO_DEFAULT_CHANNEL);
}

int16_t Qwilino_Potentiometer::read(uint8_t channel) {
  if (channel > 3) return 0;

  uint16_t config = 0x8183; 
  config |= _gain;

  switch (channel) {
    case 0: config |= 0x4000; break;
    case 1: config |= 0x5000; break;
    case 2: config |= 0x6000; break;
    case 3: config |= 0x7000; break;
  }

  writeRegister(ADS1015_REG_POINTER_CONFIG, config);
  delay(1);

  uint16_t res = readRegister(ADS1015_REG_POINTER_CONVERT);
  
  int16_t rawValue = (int16_t)(res >> 4); 

  int16_t mappedValue = map(rawValue, 0, 1648, 0, 1023);

  if (mappedValue > 1023) mappedValue = 1023;
  if (mappedValue < 0) mappedValue = 0;

  return mappedValue; 
}

void Qwilino_Potentiometer::writeRegister(uint8_t reg, uint16_t value) {
  if (!_wire) return;
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write((uint8_t)(value >> 8));
  _wire->write((uint8_t)(value & 0xFF));
  _wire->endTransmission();
}

uint16_t Qwilino_Potentiometer::readRegister(uint8_t reg) {
  if (!_wire) return 0;
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->endTransmission();

  _wire->requestFrom((uint8_t)_address, (size_t)2);
  if (_wire->available() == 2) {
    uint16_t value = _wire->read() << 8;
    value |= _wire->read();
    return value;
  }
  return 0;
}
