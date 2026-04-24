#include "Qwilino_Distance.h"

#define SENSOR_I2C_ADDR 0x29 

QwilinoDistance::QwilinoDistance() {
  _sensor = nullptr;
  _lastDistanceMM = 0;
}

bool QwilinoDistance::begin(TwoWire *wire) {
  _wire = wire;
  _wire->begin();
  _wire->setClock(400000); 
  
  delay(100);

  if (_sensor == nullptr) {
    _sensor = new VL53L4CD(_wire, -1);
  }

  _sensor->begin();
  
  uint8_t error = 0;
  for (int i = 0; i < 5; i++) {
     error = _sensor->InitSensor(SENSOR_I2C_ADDR);
     if(error == 0) break; 
     delay(100);
  }

  if (error != 0) {
    return false;
  }

  _sensor->VL53L4CD_SetRangeTiming(50, 0);
  _sensor->VL53L4CD_StartRanging();

  return true;
}

bool QwilinoDistance::available() {
  if (_sensor == nullptr) return false;

  uint8_t dataReady = 0;
  uint8_t status = 0;
  VL53L4CD_Result_t results;

  status = _sensor->VL53L4CD_CheckForDataReady(&dataReady);

  if ((status == 0) && (dataReady != 0)) {
    _sensor->VL53L4CD_GetResult(&results);
    _sensor->VL53L4CD_ClearInterrupt();
    
    if (results.range_status == 0) {
      _lastDistanceMM = results.distance_mm;
    }
    return true;
  }
  return false;
}

uint16_t QwilinoDistance::get() {
  return _lastDistanceMM;
}