#ifndef Qwilino_LED_Matrix_h
#define Qwilino_LED_Matrix_h

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
  #define QWILINO_MATRIX_DEFAULT_WIRE Wire1
#else
  #define QWILINO_MATRIX_DEFAULT_WIRE Wire
#endif

#define QWILINO_MATRIX_DEFAULT_ADDR 0x32
#define REG_FRAME_DATA 0x01

class Qwilino_LED_Matrix {
  public:
    Qwilino_LED_Matrix(uint8_t i2c_addr = QWILINO_MATRIX_DEFAULT_ADDR);
    bool begin(TwoWire &wirePort = QWILINO_MATRIX_DEFAULT_WIRE);
    
    void clear();
    void setPixel(int8_t x, int8_t y, bool state);
    void show();
    void loadFrame(const uint32_t frame[3]);
    
    void drawChar(int8_t x, int8_t y, char c);
    void printText(const char* text, int8_t x = 0, int8_t y = 0);
    void scrollText(const char* text, uint16_t speed_ms = 100);

  private:
    uint8_t _i2c_addr;
    TwoWire *_i2c;
    uint8_t _buffer[12];
};

extern const uint32_t Qwilino_Gallery_Heart[3];
extern const uint32_t Qwilino_Gallery_Smile[3];
extern const uint32_t Qwilino_Gallery_Sad[3];
extern const uint32_t Qwilino_Gallery_Check[3];
extern const uint32_t Qwilino_Gallery_Cross[3];
extern const uint32_t Qwilino_Gallery_ArrowUp[3];
extern const uint32_t Qwilino_Gallery_ArrowDown[3];

#endif