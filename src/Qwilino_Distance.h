#ifndef QWILINO_DISTANCE_H
#define QWILINO_DISTANCE_H

#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cd_class.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_DISTANCE_DEFAULT_WIRE Wire1
#else
  #define QWILINO_DISTANCE_DEFAULT_WIRE Wire
#endif

class QwilinoDistance {
public:
  QwilinoDistance();

  bool begin(TwoWire *wire = &QWILINO_DISTANCE_DEFAULT_WIRE);
  bool available();
  uint16_t get();

private:
  TwoWire *_wire;
  VL53L4CD *_sensor;
  uint16_t _lastDistanceMM;
};

#endif