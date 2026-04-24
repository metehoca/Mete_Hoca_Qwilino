// ──────────────────────────────────────────────────────────────
//  Qwilino_Temp — TMP1075 I2C Temperature Sensor Library
//  Chip: Texas Instruments TMP1075
//  Device ID: 0x7500 (register 0x0F)
//
//  I2C Address Map (7-bit):
//  ┌─────────────────────────┬──────┬─────────────────────────┐
//  │ A2    A1    A0          │ Addr │ Constant                │
//  ├─────────────────────────┼──────┼─────────────────────────┤
//  │ GND   GND   GND         │ 0x48 │ TMP1075_ADDR_ALL_GND    │
//  │ GND   GND   VCC         │ 0x49 │ TMP1075_ADDR_A0_VCC     │
//  │ GND   VCC   GND         │ 0x4A │ TMP1075_ADDR_A1_VCC     │
//  │ GND   VCC   VCC         │ 0x4B │ TMP1075_ADDR_A1A0_VCC   │
//  │ VCC   GND   GND         │ 0x4C │ TMP1075_ADDR_A2_VCC     │
//  │ VCC   GND   VCC         │ 0x4D │ TMP1075_ADDR_A2A0_VCC   │
//  │ VCC   VCC   GND         │ 0x4E │ TMP1075_ADDR_A2A1_VCC   │
//  │ VCC   VCC   VCC         │ 0x4F │ TMP1075_ADDR_ALL_VCC    │
//  └─────────────────────────┴──────┴─────────────────────────┘
//
//  Default address: 0x49
// ──────────────────────────────────────────────────────────────

#ifndef QWILINO_TEMP_H
#define QWILINO_TEMP_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_TEMP_DEFAULT_WIRE Wire1
#else
  #define QWILINO_TEMP_DEFAULT_WIRE Wire
#endif

#define TMP1075_ADDR_ALL_GND    0x48
#define TMP1075_ADDR_A0_VCC     0x49
#define TMP1075_ADDR_A1_VCC     0x4A
#define TMP1075_ADDR_A1A0_VCC   0x4B
#define TMP1075_ADDR_A2_VCC     0x4C
#define TMP1075_ADDR_A2A0_VCC   0x4D
#define TMP1075_ADDR_A2A1_VCC   0x4E
#define TMP1075_ADDR_ALL_VCC    0x4F

#define TMP1075_REG_TEMP        0x00
#define TMP1075_REG_CFG         0x01
#define TMP1075_REG_DIEID       0x0F

class Qwilino_Temp {
public:
    explicit Qwilino_Temp(uint8_t address = TMP1075_ADDR_A0_VCC,
                          TwoWire &wirePort = QWILINO_TEMP_DEFAULT_WIRE);

    bool begin(bool initWire = true);

    float readTempC();
    float readTempF();
    float readTempK();

    void shutdown(bool enable);
    float oneShot();

    uint16_t getDeviceID();
    bool isConnected();

private:
    uint8_t _addr;
    TwoWire *_wire;

    void writeRegister(uint8_t reg, uint16_t value);
    uint16_t readRegister(uint8_t reg);
    float rawToTempC(uint16_t raw);
};

#endif