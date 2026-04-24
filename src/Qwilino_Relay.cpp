#include "Qwilino_Relay.h"

Qwilino_Relay::Qwilino_Relay(uint8_t address) {
  _address = address;
  _currentState = false;
}

bool Qwilino_Relay::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;
  _i2cPort->begin();
  _i2cPort->beginTransmission(_address);
  return (_i2cPort->endTransmission() == 0);
}

void Qwilino_Relay::set() {
  writeCommand(0x01);
  _currentState = true;
}

void Qwilino_Relay::reset() {
  writeCommand(0x00);
  _currentState = false;
}

void Qwilino_Relay::toggle() {
  if (_currentState) {
    reset();
  } else {
    set();
  }
}

bool Qwilino_Relay::getState() {
  return _currentState;
}

void Qwilino_Relay::writeCommand(uint8_t command) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(0x10);
  _i2cPort->write(command);
  _i2cPort->endTransmission();
}