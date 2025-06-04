#include "ES8388Codec.h"

#define ES8388_ADDR 0x10

// Register definitions
#define ES8388_CONTROL2       0x01
#define ES8388_CHIPPOWER      0x02
#define ES8388_ADCPOWER       0x03
#define ES8388_DACPOWER       0x04
#define ES8388_MASTERMODE     0x08
#define ES8388_ADCCONTROL1    0x09
#define ES8388_ADCCONTROL2    0x0a
#define ES8388_ADCCONTROL3    0x0b
#define ES8388_ADCCONTROL4    0x0c
#define ES8388_ADCCONTROL5    0x0d
#define ES8388_ADCCONTROL8    0x10
#define ES8388_ADCCONTROL9    0x11
#define ES8388_ADCCONTROL10   0x12
#define ES8388_ADCCONTROL11   0x13
#define ES8388_ADCCONTROL12   0x14
#define ES8388_ADCCONTROL13   0x15
#define ES8388_ADCCONTROL14   0x16
#define ES8388_DACCONTROL1    0x17
#define ES8388_DACCONTROL2    0x18
#define ES8388_DACCONTROL3    0x19
#define ES8388_DACCONTROL4    0x1a
#define ES8388_DACCONTROL5    0x1b
#define ES8388_DACCONTROL7    0x1d
#define ES8388_DACCONTROL16   0x26
#define ES8388_DACCONTROL17   0x27
#define ES8388_DACCONTROL20   0x2a
#define ES8388_DACCONTROL21   0x2b
#define ES8388_DACCONTROL23   0x2d
#define ES8388_DACCONTROL24   0x2e
#define ES8388_DACCONTROL25   0x2f
#define ES8388_DACCONTROL26   0x30
#define ES8388_DACCONTROL27   0x31

bool ES8388Codec::writeReg(uint8_t reg, uint8_t val) {
    if (!m_wire) return false;
    m_wire->beginTransmission(ES8388_ADDR);
    m_wire->write(reg);
    m_wire->write(val);
    return m_wire->endTransmission() == 0;
}

bool ES8388Codec::begin(TwoWire &wire, int sda, int scl, uint32_t frequency) {
    m_wire = &wire;
    m_wire->begin(sda, scl, frequency);
    m_wire->beginTransmission(ES8388_ADDR);
    if (m_wire->endTransmission() != 0) {
        return false;
    }

    bool ok = true;
    ok &= writeReg(ES8388_DACCONTROL3, 0x04);
    ok &= writeReg(ES8388_CONTROL2, 0x50);
    ok &= writeReg(ES8388_CHIPPOWER, 0x00);
    ok &= writeReg(ES8388_MASTERMODE, 0x00);
    ok &= writeReg(ES8388_DACPOWER, 0x3e);
    ok &= writeReg(0x00, 0x12); // CONTROL1
    ok &= writeReg(ES8388_DACCONTROL1, 0x18);
    ok &= writeReg(ES8388_DACCONTROL2, 0x02);
    ok &= writeReg(ES8388_DACCONTROL16, 0x1B);
    ok &= writeReg(ES8388_DACCONTROL17, 0x90);
    ok &= writeReg(ES8388_DACCONTROL20, 0x90);
    ok &= writeReg(ES8388_DACCONTROL21, 0x80);
    ok &= writeReg(ES8388_DACCONTROL23, 0x00);
    ok &= writeReg(ES8388_DACCONTROL5, 0x00);
    ok &= writeReg(ES8388_DACCONTROL4, 0x00);
    ok &= writeReg(ES8388_ADCPOWER, 0xff);
    ok &= writeReg(ES8388_ADCCONTROL1, 0x88);
    ok &= writeReg(ES8388_ADCCONTROL2, 0xFC);
    ok &= writeReg(ES8388_ADCCONTROL3, 0x02);
    ok &= writeReg(ES8388_ADCCONTROL4, 0x0c);
    ok &= writeReg(ES8388_ADCCONTROL5, 0x02);
    ok &= writeReg(ES8388_ADCCONTROL8, 0x00);
    ok &= writeReg(ES8388_ADCCONTROL9, 0x00);
    ok &= writeReg(ES8388_ADCCONTROL10, 0xf8);
    ok &= writeReg(ES8388_ADCCONTROL11, 0x30);
    ok &= writeReg(ES8388_ADCCONTROL12, 0x57);
    ok &= writeReg(ES8388_ADCCONTROL13, 0x06);
    ok &= writeReg(ES8388_ADCCONTROL14, 0x89);
    ok &= writeReg(ES8388_DACCONTROL7, 0x20);
    ok &= writeReg(ES8388_DACCONTROL24, 0x21);
    ok &= writeReg(ES8388_DACCONTROL25, 0x21);
    ok &= writeReg(ES8388_DACCONTROL26, 0x21);
    ok &= writeReg(ES8388_DACCONTROL27, 0x21);
    ok &= writeReg(ES8388_DACPOWER, 0x3C);
    ok &= writeReg(ES8388_DACCONTROL3, 0x00);
    ok &= writeReg(ES8388_ADCPOWER, 0x00);
    return ok;
}

void ES8388Codec::setVolume(uint8_t mainVolume, uint8_t out1Volume) {
    if (!m_wire) return;
    uint8_t main = 96 - (mainVolume > 100 ? 96 : (96 * mainVolume) / 100);
    writeReg(ES8388_DACCONTROL4, main);
    writeReg(ES8388_DACCONTROL5, main);
    uint8_t out = (0x21 * out1Volume) / 100;
    writeReg(ES8388_DACCONTROL24, out);
    writeReg(ES8388_DACCONTROL25, out);
}

