#ifndef QWILINO_POTENTIOMETER_H
#define QWILINO_POTENTIOMETER_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_POTENTIOMETER_DEFAULT_WIRE Wire1
#else
  #define QWILINO_POTENTIOMETER_DEFAULT_WIRE Wire
#endif

#define QWILINO_DEFAULT_CHANNEL 3

typedef enum {
  QWILINO_POTENTIOMETER_PGA_2_3 = 0x0000,
  QWILINO_POTENTIOMETER_PGA_1   = 0x0200,
  QWILINO_POTENTIOMETER_PGA_2   = 0x0400,
  QWILINO_POTENTIOMETER_PGA_4   = 0x0600,
  QWILINO_POTENTIOMETER_PGA_8   = 0x0800,
  QWILINO_POTENTIOMETER_PGA_16  = 0x0A00
} Qwilino_Potentiometer_Gain;

class Qwilino_Potentiometer {
  public:
    Qwilino_Potentiometer();
    
    bool begin(uint8_t address = 0x48, TwoWire &wirePort = QWILINO_POTENTIOMETER_DEFAULT_WIRE);
    void setGain(Qwilino_Potentiometer_Gain gain);
    
    int16_t read(); 
    int16_t read(uint8_t channel);

  private:
    uint8_t _address;
    TwoWire *_wire;
    Qwilino_Potentiometer_Gain _gain;

    void writeRegister(uint8_t reg, uint16_t value);
    uint16_t readRegister(uint8_t reg);
};

#endif
