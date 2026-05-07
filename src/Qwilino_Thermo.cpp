#include "Qwilino_Thermo.h"

QwilinoThermo::QwilinoThermo(uint8_t address) {
  _address = address;
  _wire = &QWILINO_THERMO_DEFAULT_WIRE;
  _lastTemp = 0.0;
  _lastHum = 0.0;
}

bool QwilinoThermo::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

void QwilinoThermo::readSensor() {
  _wire->beginTransmission(_address);
  _wire->endTransmission();
  
  delay(40);
  
  uint8_t num = _wire->requestFrom((uint8_t)_address, (size_t)4);
  
  if (num == 4) {
    uint8_t data[4];
    data[0] = _wire->read();
    data[1] = _wire->read();
    data[2] = _wire->read();
    data[3] = _wire->read();

    uint16_t humC = ((data[0] & 0x3F) << 8) | data[1];
    _lastHum = (humC * 100.0) / 16383.0;

    uint16_t tempC = (data[2] << 6) | ((data[3] & 0xFC) >> 2);
    _lastTemp = (tempC * 165.0 / 16383.0) - 40.0;
  }
}

void QwilinoThermo::update() {
  readSensor();
}

float QwilinoThermo::getTemperature() {
  readSensor();
  return _lastTemp;
}

float QwilinoThermo::getHumidity() {
  readSensor();
  return _lastHum;
}

float QwilinoThermo::readLastTemperature() {
  return _lastTemp;
}

float QwilinoThermo::readLastHumidity() {
  return _lastHum;
}