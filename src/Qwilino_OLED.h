#ifndef QWILINO_OLED_H
#define QWILINO_OLED_H

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_OLED_DEFAULT_WIRE Wire1
#else
  #define QWILINO_OLED_DEFAULT_WIRE Wire
#endif

#if !defined(__AVR__)
  #ifndef pgm_read_byte
    #define pgm_read_byte(addr) (*(const uint8_t *)(addr))
  #endif
#endif

#ifndef QWILINO_WIRE_CHUNK
  #define QWILINO_WIRE_CHUNK 30
#endif

class Qwilino_OLED {
  private:
    uint8_t   _i2cAddress;
    TwoWire  *_wire;
    bool      _connected;

    void sendCommand(uint8_t command);
    void sendDataChunk(const uint8_t *buf, uint8_t len);
    void sendDataByte(uint8_t data);

    void setCursor(uint8_t col, uint8_t page);
    void printChar(char c);

  public:
    Qwilino_OLED(uint8_t address = 0x3D);

    bool begin(TwoWire *wire = &QWILINO_OLED_DEFAULT_WIRE,
               uint32_t hz  = 400000UL);

    bool isConnected() const { return _connected; }

    void clear();
    void clearLine(int line);
    void wake();
    void sleep();
    void invertDisplay(bool invert);

    void printString(uint8_t col, uint8_t page, const char *text);

    void printLine(const char *text, int line, bool center = false);
    void printLine(const __FlashStringHelper *text, int line, bool center = false);

    void printLine(int    value, int line, bool center = false);
    void printLine(long   value, int line, bool center = false);
    void printLine(double value, int line, int decimals = 2, bool center = false);

    void printLine(const char *label, int    value, int line, bool center = false);
    void printLine(const char *label, long   value, int line, bool center = false);
    void printLine(const char *label, double value, int line,
                   int decimals = 2, bool center = false);
};

#endif /* QWILINO_OLED_H */