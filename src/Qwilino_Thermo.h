#ifndef QWILINO_THERMO_H
#define QWILINO_THERMO_H

#include <Arduino.h>
#include <Wire.h>

#define QWILINO_THERMO_ADDR 0x44

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_THERMO_DEFAULT_WIRE Wire1
#else
  #define QWILINO_THERMO_DEFAULT_WIRE Wire
#endif

class QwilinoThermo {
public:
  QwilinoThermo(uint8_t address = QWILINO_THERMO_ADDR);
  
  bool begin(TwoWire *wire = &QWILINO_THERMO_DEFAULT_WIRE);
  
  float getTemperature();
  float getHumidity();
  
  void update();
  float readLastTemperature();
  float readLastHumidity();

private:
  uint8_t _address;
  TwoWire *_wire;
  float _lastTemp;
  float _lastHum;
  
  void readSensor();
};

#endif