#include "Qwilino_Temp.h"

Qwilino_Temp::Qwilino_Temp(uint8_t address, TwoWire &wirePort)
    : _addr(address), _wire(&wirePort) {}

bool Qwilino_Temp::begin(bool initWire) {
    if (initWire) {
        _wire->begin();
    }

    if (!isConnected()) return false;

    uint16_t id = getDeviceID();
    return (id == 0x7500);
}

float Qwilino_Temp::readTempC() {
    return rawToTempC(readRegister(TMP1075_REG_TEMP));
}

float Qwilino_Temp::readTempF() {
    return readTempC() * 9.0f / 5.0f + 32.0f;
}

float Qwilino_Temp::readTempK() {
    return readTempC() + 273.15f;
}

void Qwilino_Temp::shutdown(bool enable) {
    uint16_t cfg = readRegister(TMP1075_REG_CFG);
    if (enable) {
        cfg |= 0x0100; 
    } else {
        cfg &= ~0x0100;
    }
    writeRegister(TMP1075_REG_CFG, cfg);
}

float Qwilino_Temp::oneShot() {
    uint16_t cfg = readRegister(TMP1075_REG_CFG);
    cfg |= 0x8000; 
    writeRegister(TMP1075_REG_CFG, cfg);
    
    delay(35);

    return readTempC();
}

uint16_t Qwilino_Temp::getDeviceID() {
    return readRegister(TMP1075_REG_DIEID);
}

bool Qwilino_Temp::isConnected() {
    _wire->beginTransmission(_addr);
    return (_wire->endTransmission() == 0);
}

void Qwilino_Temp::writeRegister(uint8_t reg, uint16_t value) {
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->write(static_cast<uint8_t>(value >> 8));
    _wire->write(static_cast<uint8_t>(value & 0xFF));
    _wire->endTransmission();
}

uint16_t Qwilino_Temp::readRegister(uint8_t reg) {
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->endTransmission(false);

    _wire->requestFrom(_addr, static_cast<uint8_t>(2));
    if (_wire->available() < 2) return 0x0000;

    uint16_t msb = _wire->read();
    uint16_t lsb = _wire->read();

    return (msb << 8) | lsb;
}

float Qwilino_Temp::rawToTempC(uint16_t raw) {
    int16_t temp = static_cast<int16_t>(raw);
    temp >>= 4; 
    return temp * 0.0625f;
}