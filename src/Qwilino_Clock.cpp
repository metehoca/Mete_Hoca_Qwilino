#include "Qwilino_Clock.h"

DateTime::DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000) year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

DateTime::DateTime(const char* date, const char* time) {
    switch (date[0]) {
        case 'J': m = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7); break;
        case 'F': m = 2; break;
        case 'M': m = (date[2] == 'r') ? 3 : 5; break;
        case 'A': m = (date[1] == 'p') ? 4 : 8; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
        default:  m = 1; break;
    }
    d    = atoi(date + 4);
    yOff = atoi(date + 7) - 2000;
    hh   = atoi(time);
    mm   = atoi(time + 3);
    ss   = atoi(time + 6);
}

Qwilino_Clock::Qwilino_Clock() {
    _wire = &QWILINO_CLOCK_DEFAULT_WIRE;
}

bool Qwilino_Clock::begin(TwoWire *wireInstance, uint8_t address) {
    _wire = wireInstance;
    _address = address;
    _wire->begin();
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() == 0);
}

void Qwilino_Clock::adjust(const DateTime& dt) {
    _wire->beginTransmission(_address);
    _wire->write(0x02); 
    _wire->write(bin2bcd(dt.second()));
    _wire->write(bin2bcd(dt.minute()));
    _wire->write(bin2bcd(dt.hour()));
    _wire->write(bin2bcd(dt.day()));
    _wire->write(0x00); 
    _wire->write(bin2bcd(dt.month()) & 0x1F);
    _wire->write(bin2bcd(dt.year() - 2000));
    _wire->endTransmission();
}

DateTime Qwilino_Clock::now() {
    _wire->beginTransmission(_address);
    _wire->write(0x02);
    _wire->endTransmission();

    _wire->requestFrom((uint8_t)_address, (size_t)7);
    uint8_t ss = bcd2bin(_wire->read() & 0x7F);
    uint8_t mm = bcd2bin(_wire->read() & 0x7F);
    uint8_t hh = bcd2bin(_wire->read() & 0x3F);
    uint8_t d  = bcd2bin(_wire->read() & 0x3F);
    _wire->read(); 
    uint8_t m  = bcd2bin(_wire->read() & 0x1F);
    uint16_t y = bcd2bin(_wire->read()) + 2000;

    return DateTime(y, m, d, hh, mm, ss);
}

bool Qwilino_Clock::lostPower() {
    return (readRegister(0x02) & 0x80) != 0;
}

void Qwilino_Clock::start() {
    uint8_t sec = readRegister(0x02);
    writeRegister(0x02, sec & 0x7F);
}

void Qwilino_Clock::stop() {
    uint8_t sec = readRegister(0x02);
    writeRegister(0x02, sec | 0x80);
}

uint8_t Qwilino_Clock::readRegister(uint8_t reg) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom((uint8_t)_address, (size_t)1);
    return _wire->read();
}

void Qwilino_Clock::writeRegister(uint8_t reg, uint8_t val) {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(val);
    _wire->endTransmission();
}

uint8_t DateTime::dayOfTheWeek() const {
    uint16_t y = year();
    uint8_t m_local = month();
    uint8_t d_local = day();
    
    // Sakamoto algoritmasý kullanýlarak haftanýn günü hesaplanýyor
    static const uint8_t t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m_local < 3;
    return (y + y/4 - y/100 + y/400 + t[m_local-1] + d_local) % 7;
}