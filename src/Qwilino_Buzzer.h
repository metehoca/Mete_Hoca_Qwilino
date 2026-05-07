#ifndef QWILINO_BUZZER_H
#define QWILINO_BUZZER_H

#include <Arduino.h>
#include <Wire.h>

#ifdef tone
  #undef tone
#endif
#ifdef noTone
  #undef noTone
#endif

#define QWILINO_BUZZER_ADDR 0x1E

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_BUZZER_DEFAULT_WIRE Wire1
#else
  #define QWILINO_BUZZER_DEFAULT_WIRE Wire
#endif

class QwilinoBuzzer {
public:
  QwilinoBuzzer(uint8_t address = QWILINO_BUZZER_ADDR);
  bool begin(TwoWire *wire = &QWILINO_BUZZER_DEFAULT_WIRE);
  void tone(uint32_t freq, uint32_t duration_ms);
  void noTone();

private:
  uint8_t _address;
  TwoWire *_wire;
  void writeModule(uint8_t* data, size_t len);
};

#endif