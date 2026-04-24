#include "Qwilino_Buzzer.h"

QwilinoBuzzer::QwilinoBuzzer(uint8_t address) {
  _address = address;
  _wire = &QWILINO_BUZZER_DEFAULT_WIRE;
}

bool QwilinoBuzzer::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

void QwilinoBuzzer::tone(uint32_t freq, uint32_t duration_ms) {
  uint8_t buf[8];
  memcpy(&buf[0], &freq, 4);
  memcpy(&buf[4], &duration_ms, 4);
  writeModule(buf, 8);
}

void QwilinoBuzzer::noTone() {
  uint8_t buf[8];
  memset(buf, 0, 8);
  writeModule(buf, 8);
}

void QwilinoBuzzer::writeModule(uint8_t* data, size_t len) {
  _wire->beginTransmission(_address);
  for (size_t i = 0; i < len; i++) { _wire->write(data[i]); }
  _wire->endTransmission();
}