#include "Qwilino_OLED.h"

static const uint8_t font5x7[][5] PROGMEM = {
  {0x00, 0x00, 0x00, 0x00, 0x00}, 
  {0x00, 0x00, 0x2F, 0x00, 0x00}, 
  {0x00, 0x07, 0x00, 0x07, 0x00}, 
  {0x14, 0x7F, 0x14, 0x7F, 0x14}, 
  {0x24, 0x2A, 0x7F, 0x2A, 0x12}, 
  {0x23, 0x13, 0x08, 0x64, 0x62}, 
  {0x36, 0x49, 0x55, 0x22, 0x50}, 
  {0x00, 0x05, 0x03, 0x00, 0x00}, 
  {0x00, 0x1C, 0x22, 0x41, 0x00}, 
  {0x00, 0x41, 0x22, 0x1C, 0x00}, 
  {0x14, 0x08, 0x3E, 0x08, 0x14}, 
  {0x08, 0x08, 0x3E, 0x08, 0x08}, 
  {0x00, 0x50, 0x30, 0x00, 0x00}, 
  {0x08, 0x08, 0x08, 0x08, 0x08}, 
  {0x00, 0x60, 0x60, 0x00, 0x00}, 
  {0x20, 0x10, 0x08, 0x04, 0x02}, 
  {0x3E, 0x51, 0x49, 0x45, 0x3E}, 
  {0x00, 0x42, 0x7F, 0x40, 0x00}, 
  {0x42, 0x61, 0x51, 0x49, 0x46}, 
  {0x21, 0x41, 0x45, 0x4B, 0x31}, 
  {0x18, 0x14, 0x12, 0x7F, 0x10}, 
  {0x27, 0x45, 0x45, 0x45, 0x39}, 
  {0x3C, 0x4A, 0x49, 0x49, 0x30}, 
  {0x01, 0x71, 0x09, 0x05, 0x03}, 
  {0x36, 0x49, 0x49, 0x49, 0x36}, 
  {0x06, 0x49, 0x49, 0x29, 0x1E}, 
  {0x00, 0x36, 0x36, 0x00, 0x00}, 
  {0x00, 0x56, 0x36, 0x00, 0x00}, 
  {0x08, 0x14, 0x22, 0x41, 0x00}, 
  {0x14, 0x14, 0x14, 0x14, 0x14}, 
  {0x00, 0x41, 0x22, 0x14, 0x08}, 
  {0x02, 0x01, 0x51, 0x09, 0x06}, 
  {0x32, 0x49, 0x79, 0x41, 0x3E}, 
  {0x7E, 0x11, 0x11, 0x11, 0x7E}, 
  {0x7F, 0x49, 0x49, 0x49, 0x36}, 
  {0x3E, 0x41, 0x41, 0x41, 0x22}, 
  {0x7F, 0x41, 0x41, 0x22, 0x1C}, 
  {0x7F, 0x49, 0x49, 0x49, 0x41}, 
  {0x7F, 0x09, 0x09, 0x09, 0x01}, 
  {0x3E, 0x41, 0x49, 0x49, 0x7A}, 
  {0x7F, 0x08, 0x08, 0x08, 0x7F}, 
  {0x00, 0x41, 0x7F, 0x41, 0x00}, 
  {0x20, 0x40, 0x41, 0x3F, 0x01}, 
  {0x7F, 0x08, 0x14, 0x22, 0x41}, 
  {0x7F, 0x40, 0x40, 0x40, 0x40}, 
  {0x7F, 0x02, 0x0C, 0x02, 0x7F}, 
  {0x7F, 0x04, 0x08, 0x10, 0x7F}, 
  {0x3E, 0x41, 0x41, 0x41, 0x3E}, 
  {0x7F, 0x09, 0x09, 0x09, 0x06}, 
  {0x3E, 0x41, 0x51, 0x21, 0x5E}, 
  {0x7F, 0x09, 0x19, 0x29, 0x46}, 
  {0x46, 0x49, 0x49, 0x49, 0x31}, 
  {0x01, 0x01, 0x7F, 0x01, 0x01}, 
  {0x3F, 0x40, 0x40, 0x40, 0x3F}, 
  {0x1F, 0x20, 0x40, 0x20, 0x1F}, 
  {0x3F, 0x40, 0x38, 0x40, 0x3F}, 
  {0x63, 0x14, 0x08, 0x14, 0x63}, 
  {0x07, 0x08, 0x70, 0x08, 0x07}, 
  {0x61, 0x51, 0x49, 0x45, 0x43}, 
  {0x00, 0x7F, 0x41, 0x41, 0x00}, 
  {0x02, 0x04, 0x08, 0x10, 0x20}, 
  {0x00, 0x41, 0x41, 0x7F, 0x00}, 
  {0x04, 0x02, 0x01, 0x02, 0x04}, 
  {0x40, 0x40, 0x40, 0x40, 0x40}, 
  {0x00, 0x01, 0x02, 0x04, 0x00}, 
  {0x20, 0x54, 0x54, 0x54, 0x78}, 
  {0x7F, 0x48, 0x44, 0x44, 0x38}, 
  {0x38, 0x44, 0x44, 0x44, 0x20}, 
  {0x38, 0x44, 0x44, 0x48, 0x7F}, 
  {0x38, 0x54, 0x54, 0x54, 0x18}, 
  {0x08, 0x7E, 0x09, 0x01, 0x02}, 
  {0x18, 0xA4, 0xA4, 0xA4, 0x7C}, 
  {0x7F, 0x08, 0x04, 0x04, 0x78}, 
  {0x00, 0x44, 0x7D, 0x40, 0x00}, 
  {0x40, 0x80, 0x84, 0x7D, 0x00}, 
  {0x7F, 0x10, 0x28, 0x44, 0x00}, 
  {0x00, 0x41, 0x7F, 0x40, 0x00}, 
  {0x7C, 0x04, 0x18, 0x04, 0x78}, 
  {0x7C, 0x08, 0x04, 0x04, 0x78}, 
  {0x38, 0x44, 0x44, 0x44, 0x38}, 
  {0xFC, 0x24, 0x24, 0x24, 0x18}, 
  {0x18, 0x24, 0x24, 0x18, 0xFC}, 
  {0x7C, 0x08, 0x04, 0x04, 0x08}, 
  {0x48, 0x54, 0x54, 0x54, 0x20}, 
  {0x04, 0x3F, 0x44, 0x40, 0x20}, 
  {0x3C, 0x40, 0x40, 0x20, 0x7C}, 
  {0x1C, 0x20, 0x40, 0x20, 0x1C}, 
  {0x3C, 0x40, 0x30, 0x40, 0x3C}, 
  {0x44, 0x28, 0x10, 0x28, 0x44}, 
  {0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, 
  {0x44, 0x64, 0x54, 0x4C, 0x44}, 
  {0x00, 0x08, 0x36, 0x41, 0x00}, 
  {0x00, 0x00, 0x7F, 0x00, 0x00}, 
  {0x00, 0x41, 0x36, 0x08, 0x00}, 
  {0x10, 0x08, 0x18, 0x10, 0x08}  
};

static void copyFlashStr(const __FlashStringHelper *src,
                         char *dst, uint8_t maxLen)
{
    PGM_P p = reinterpret_cast<PGM_P>(src);
    uint8_t i = 0;
    char c;
    while ((c = (char)pgm_read_byte(p++)) != '\0' && i < maxLen - 1)
        dst[i++] = c;
    dst[i] = '\0';
}

Qwilino_OLED::Qwilino_OLED(uint8_t address)
    : _i2cAddress(address),
      _wire(&QWILINO_OLED_DEFAULT_WIRE),
      _connected(false)
{}

void Qwilino_OLED::sendCommand(uint8_t command)
{
    _wire->beginTransmission(_i2cAddress);
    _wire->write(0x00);      
    _wire->write(command);
    _wire->endTransmission();
}

void Qwilino_OLED::sendDataChunk(const uint8_t *buf, uint8_t len)
{
    uint8_t sent = 0;
    while (sent < len) {
        uint8_t chunk = (len - sent < QWILINO_WIRE_CHUNK)
                        ? (len - sent)
                        : QWILINO_WIRE_CHUNK;
        _wire->beginTransmission(_i2cAddress);
        _wire->write(0x40);          
        for (uint8_t i = 0; i < chunk; i++)
            _wire->write(buf[sent + i]);
        _wire->endTransmission();
        sent += chunk;
    }
}

void Qwilino_OLED::sendDataByte(uint8_t data)
{
    _wire->beginTransmission(_i2cAddress);
    _wire->write(0x40);
    _wire->write(data);
    _wire->endTransmission();
}

bool Qwilino_OLED::begin(TwoWire *wire, uint32_t hz)
{
    _wire = wire;
    _wire->begin();
    _wire->setClock(hz);

    _wire->beginTransmission(_i2cAddress);
    uint8_t err = _wire->endTransmission();
    if (err != 0) {
        _connected = false;
        return false;           
    }
    _connected = true;

    sendCommand(0xAE);          
    sendCommand(0xD5); sendCommand(0x80); 
    sendCommand(0xA8); sendCommand(0x3F); 
    sendCommand(0xD3); sendCommand(0x00); 
    sendCommand(0x40);                    
    sendCommand(0x8D); sendCommand(0x14); 
    sendCommand(0x20); sendCommand(0x00); 
    sendCommand(0xA1);                    
    sendCommand(0xC8);                    
    sendCommand(0xDA); sendCommand(0x12); 
    sendCommand(0x81); sendCommand(0xCF); 
    sendCommand(0xD9); sendCommand(0xF1); 
    sendCommand(0xDB); sendCommand(0x40); 
    sendCommand(0xA4);                    
    sendCommand(0xA6);                    
    sendCommand(0xAF);                    

    clear();
    return true;
}

void Qwilino_OLED::clear()
{
    static const uint8_t zeros[QWILINO_WIRE_CHUNK] = {0};

    for (uint8_t page = 0; page < 8; page++) {
        setCursor(0, page);

        uint8_t remaining = 128;
        while (remaining > 0) {
            uint8_t chunk = (remaining < QWILINO_WIRE_CHUNK)
                            ? remaining
                            : QWILINO_WIRE_CHUNK;
            sendDataChunk(zeros, chunk);
            remaining -= chunk;
        }
    }
}

void Qwilino_OLED::clearLine(int line)
{
    if (line < 0 || line > 3) return;

    uint8_t page = (uint8_t)line * 2;

    static const uint8_t zeros[QWILINO_WIRE_CHUNK] = {0};

    setCursor(0, page);
    uint8_t remaining = 128;
    while (remaining > 0) {
        uint8_t chunk = (remaining < QWILINO_WIRE_CHUNK)
                        ? remaining
                        : QWILINO_WIRE_CHUNK;
        sendDataChunk(zeros, chunk);
        remaining -= chunk;
    }
}

void Qwilino_OLED::sleep()        { sendCommand(0xAE); }
void Qwilino_OLED::wake()         { sendCommand(0xAF); }

void Qwilino_OLED::invertDisplay(bool invert)
{
    sendCommand(invert ? 0xA7 : 0xA6);
}

void Qwilino_OLED::setCursor(uint8_t col, uint8_t page)
{
    sendCommand(0x22);   
    sendCommand(page);
    sendCommand(7);
    sendCommand(0x21);   
    sendCommand(col);
    sendCommand(127);
}

void Qwilino_OLED::printChar(char c)
{
    if (c < 32 || c > 126) c = 32;   

    uint8_t idx = (uint8_t)(c - 32);
    
    uint8_t buf[6];
    for (uint8_t i = 0; i < 5; i++)
        buf[i] = pgm_read_byte(&font5x7[idx][i]);
    buf[5] = 0x00;   
    sendDataChunk(buf, 6);
}

void Qwilino_OLED::printString(uint8_t col, uint8_t page, const char *text)
{
    setCursor(col, page);
    while (*text)
        printChar(*text++);
}

void Qwilino_OLED::printLine(const char *text, int line, bool center)
{
    if (line < 0 || line > 3 || !text) return;
    uint8_t page = (uint8_t)line * 2;

    clearLine(line);

    uint8_t startCol = 0;
    if (center) {
        uint8_t len = 0;
        while (text[len] != '\0') len++;
        uint16_t px = (uint16_t)len * 6;
        if (px < 128) startCol = (uint8_t)((128 - px) / 2);
    }

    printString(startCol, page, text);
}

void Qwilino_OLED::printLine(const __FlashStringHelper *text,
                              int line, bool center)
{
    char buf[22];
    copyFlashStr(text, buf, sizeof(buf));
    printLine(buf, line, center);
}

#if !defined(__AVR__) && !defined(ARDUINO_ARCH_AVR)
  #include <stdio.h>
  static char *_dtostrf(double val, int8_t width, uint8_t prec, char *s) {
      (void)width;
      sprintf(s, "%.*f", prec, val);
      return s;
  }
  #define DTOSTRF(v, w, p, s) _dtostrf(v, w, p, s)
#else
  #define DTOSTRF(v, w, p, s) dtostrf(v, w, p, s)
#endif

void Qwilino_OLED::printLine(int value, int line, bool center)
{
    char buf[12];                  
    ltoa((long)value, buf, 10);
    printLine(buf, line, center);
}

void Qwilino_OLED::printLine(long value, int line, bool center)
{
    char buf[12];
    ltoa(value, buf, 10);
    printLine(buf, line, center);
}

void Qwilino_OLED::printLine(double value, int line,
                              int decimals, bool center)
{
    char buf[16];
    DTOSTRF(value, 1, (uint8_t)decimals, buf);
    printLine(buf, line, center);
}

void Qwilino_OLED::printLine(const char *label, int value,
                              int line, bool center)
{
    char vbuf[12];
    ltoa((long)value, vbuf, 10);

    char buf[22];
    uint8_t li = 0;
    for (; label[li] && li < 21; li++) buf[li] = label[li];
    for (uint8_t vi = 0; vbuf[vi] && li < 21; vi++, li++) buf[li] = vbuf[vi];
    buf[li] = '\0';

    printLine(buf, line, center);
}

void Qwilino_OLED::printLine(const char *label, long value,
                              int line, bool center)
{
    char vbuf[12];
    ltoa(value, vbuf, 10);

    char buf[22];
    uint8_t li = 0;
    for (; label[li] && li < 21; li++) buf[li] = label[li];
    for (uint8_t vi = 0; vbuf[vi] && li < 21; vi++, li++) buf[li] = vbuf[vi];
    buf[li] = '\0';

    printLine(buf, line, center);
}

void Qwilino_OLED::printLine(const char *label, double value,
                              int line, int decimals, bool center)
{
    char vbuf[16];
    DTOSTRF(value, 1, (uint8_t)decimals, vbuf);

    char buf[22];
    uint8_t li = 0;
    for (; label[li] && li < 21; li++) buf[li] = label[li];
    for (uint8_t vi = 0; vbuf[vi] && li < 21; vi++, li++) buf[li] = vbuf[vi];
    buf[li] = '\0';

    printLine(buf, line, center);
}