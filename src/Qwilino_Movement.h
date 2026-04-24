#ifndef QWILINO_MOVEMENT_H
#define QWILINO_MOVEMENT_H

#include <Arduino.h>
#include <Wire.h>
#include <Arduino_LSM6DSOX.h> 

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_MOVEMENT_DEFAULT_WIRE Wire1
#else
  #define QWILINO_MOVEMENT_DEFAULT_WIRE Wire
#endif

class QwilinoMovement {
public:
  QwilinoMovement();
  ~QwilinoMovement(); 

  bool begin(TwoWire *wire = &QWILINO_MOVEMENT_DEFAULT_WIRE);
  bool update();

  float getX();
  float getY();
  float getZ();

  float getRoll();  
  float getPitch(); 
  float getYaw();   

private:
  TwoWire *_wire;
  LSM6DSOXClass *_imu;
  
  float _ax, _ay, _az;
  float _gx, _gy, _gz;
};

#endif