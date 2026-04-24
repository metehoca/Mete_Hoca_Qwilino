#include "Qwilino_Movement.h"

QwilinoMovement::QwilinoMovement() {
  _imu = nullptr;
  _ax = 0; _ay = 0; _az = 0;
  _gx = 0; _gy = 0; _gz = 0;
}

QwilinoMovement::~QwilinoMovement() {
  if (_imu != nullptr) {
    delete _imu;
  }
}

bool QwilinoMovement::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  
  if (_imu == nullptr) {
    _imu = new LSM6DSOXClass(*_wire, 0x6A);
  }

  if (!_imu->begin()) {
    return false;
  }

  _ax = _ay = _az = 0;
  _gx = _gy = _gz = 0;

  return true;
}

bool QwilinoMovement::update() {
  if (_imu == nullptr) return false;

  bool newData = false;

  if (_imu->accelerationAvailable()) {
    _imu->readAcceleration(_ax, _ay, _az);
    newData = true;
  }

  if (_imu->gyroscopeAvailable()) {
    _imu->readGyroscope(_gx, _gy, _gz);
    newData = true;
  }

  return newData;
}

float QwilinoMovement::getX() { return _ax; }
float QwilinoMovement::getY() { return _ay; }
float QwilinoMovement::getZ() { return _az; }

float QwilinoMovement::getRoll() { return _gx; }
float QwilinoMovement::getPitch() { return _gy; }
float QwilinoMovement::getYaw() { return _gz; }