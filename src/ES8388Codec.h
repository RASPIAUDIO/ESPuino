#pragma once

#include <Wire.h>

class ES8388Codec {
public:
    bool begin(TwoWire &wire, int sda, int scl, uint32_t frequency = 400000);
    void setVolume(uint8_t mainVolume, uint8_t out1Volume);
private:
    bool writeReg(uint8_t reg, uint8_t val);
    TwoWire *m_wire{nullptr};
};

