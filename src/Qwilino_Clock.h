#ifndef QWILINO_CLOCK_H
#define QWILINO_CLOCK_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_CLOCK_DEFAULT_WIRE Wire1
#else
  #define QWILINO_CLOCK_DEFAULT_WIRE Wire
#endif

#define PCF8563_DEFAULT_ADDRESS 0x51

class DateTime {
public:
    DateTime(uint32_t t = 0);
    DateTime(uint16_t year, uint8_t month, uint8_t day,
             uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
    DateTime(const char* date, const char* time);
    
    uint16_t year() const       { return 2000U + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    uint8_t dayOfTheWeek() const;

protected:
    uint8_t yOff, m, d, hh, mm, ss;
};

class Qwilino_Clock {
public:
    Qwilino_Clock();
    
    bool begin(TwoWire *wireInstance = &QWILINO_CLOCK_DEFAULT_WIRE,
           uint8_t address = PCF8563_DEFAULT_ADDRESS);
           
    void adjust(const DateTime& dt);
    DateTime now();
    bool lostPower();
    void start();
    void stop();

private:
    uint8_t _address;
    TwoWire* _wire;
    uint8_t bcd2bin(uint8_t val) { return val - 6 * (val >> 4); }
    uint8_t bin2bcd(uint8_t val) { return val + 6 * (val / 10); }
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t val);
};

#endif