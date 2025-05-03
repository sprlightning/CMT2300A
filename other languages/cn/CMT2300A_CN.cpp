#include <CMT2300A_CN.h>

CMT2300A::CMT2300A(uint8_t csPin) : _csPin(csPin) {
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
}

void CMT2300A::begin() {
    SPI.begin();
    // 初始化寄存器默认值
    setMode(MODE_SLEEP);
    delay(100);
    setMode(MODE_RX);  // 默认进入接收模式
}

void CMT2300A::setFrequency(uint32_t freq) {
    // 设置频率寄存器（32位）
    writeRegister(REG_FREQ_MSB, (freq >> 16) & 0xFF);
    writeRegister(REG_FREQ_MID, (freq >> 8) & 0xFF);
    writeRegister(REG_FREQ_LSB, freq & 0xFF);
}

void CMT2300A::setBandwidth(uint8_t bandwidth) {
    // 设置带宽参数
    writeRegister(REG_BW, bandwidth);
}

void CMT2300A::setPower(uint8_t power) {
    // 设置发射功率
    writeRegister(REG_POWER, power);
}

void CMT2300A::setSpreadingFactor(uint8_t sf) {
    // 设置扩频因子（6-12）
    writeRegister(REG_SF, sf);
}

void CMT2300A::setCodingRate(uint8_t rate) {
    // 设置编码率
    writeRegister(REG_CR, rate);
}

void CMT2300A::setPacketLength(uint8_t length) {
    // 设置数据包长度
    writeRegister(REG_PAC, length);
}

void CMT2300A::setLNA(uint8_t gain) {
    // 设置LNA增益
    writeRegister(REG_LNA, gain);
}

void CMT2300A::setTXFilterBandwidth(uint8_t bandwidth) {
    // 设置发射滤波器带宽
    writeRegister(REG_TX_FILTER_BW, bandwidth);
}

void CMT2300A::setRXFilterBandwidth(uint8_t bandwidth) {
    // 设置接收滤波器带宽
    writeRegister(REG_RX_FILTER_BW, bandwidth);
}

void CMT2300A::setAddress(uint64_t address) {
    // 设置64位地址（高位到低位）
    writeRegister(REG_ADDRESS_MSB, (address >> 40) & 0xFF);
    writeRegister(REG_ADDRESS_MSB + 1, (address >> 32) & 0xFF);
    writeRegister(REG_ADDRESS_MSB + 2, (address >> 24) & 0xFF);
    writeRegister(REG_ADDRESS_MSB + 3, (address >> 16) & 0xFF);
    writeRegister(REG_ADDRESS_MSB + 4, (address >> 8) & 0xFF);
    writeRegister(REG_ADDRESS_LSB, address & 0xFF);
}

void CMT2300A::setMode(uint8_t mode) {
    // 设置工作模式
    writeRegister(REG_OP_MODE, mode);
}

void CMT2300A::setPipe(uint8_t pipe, uint32_t freq, uint8_t bandwidth) {
    // 配置管道频率和带宽
    if (pipe == 0) {
        writeRegister(REG_PIPE0, (freq >> 16) & 0xFF);   // 高位
        writeRegister(REG_PIPE0 + 1, (freq >> 8) & 0xFF); // 中位
        writeRegister(REG_PIPE0 + 2, freq & 0xFF);        // 低位
        writeRegister(REG_PIPE0 + 3, bandwidth);          // 带宽
    } else if (pipe == 1) {
        writeRegister(REG_PIPE1, (freq >> 16) & 0xFF);
        writeRegister(REG_PIPE1 + 1, (freq >> 8) & 0xFF);
        writeRegister(REG_PIPE1 + 2, freq & 0xFF);
        writeRegister(REG_PIPE1 + 3, bandwidth);
    }
}

void CMT2300A::setPipeMode(uint8_t pipe, uint8_t mode) {
    // 设置管道工作模式
    if (pipe == 0) {
        writeRegister(REG_PIPE0_MODE, mode);
    } else if (pipe == 1) {
        writeRegister(REG_PIPE1_MODE, mode);
    }
}

void CMT2300A::sendMessage(uint8_t* data, uint8_t length) {
    setMode(MODE_TX);  // 进入发射模式

    // 将数据写入FIFO
    for (uint8_t i = 0; i < length; i++) {
        writeRegister(REG_FIFO, data[i]);
    }

    delay(100);        // 等待传输完成

    setMode(MODE_RX);  // 返回接收模式
}

void CMT2300A::receiveMessage(uint8_t* data, uint8_t* length) {
    setMode(MODE_RX);  // 进入接收模式
    uint8_t i = 0;
    while (i < *length) {
        data[i] = readRegister(REG_FIFO);
        i++;
    }
    *length = i;
}

void CMT2300A::writeRegister(uint8_t reg, uint8_t value) {
    digitalWrite(_csPin, LOW);
    SPI.transfer(reg | 0x80);  // 写操作标志位
    SPI.transfer(value);
    digitalWrite(_csPin, HIGH);
}

uint8_t CMT2300A::readRegister(uint8_t reg) {
    digitalWrite(_csPin, LOW);
    SPI.transfer(reg & 0x7F);   // 读操作标志位
    uint8_t value = SPI.transfer(0x00);
    digitalWrite(_csPin, HIGH);
    return value;
}

void CMT2300A::spiTransfer(uint8_t* txBuf, uint8_t* rxBuf, size_t len) {
    digitalWrite(_csPin, LOW);
    for (size_t i = 0; i < len; i++) {
        rxBuf[i] = SPI.transfer(txBuf[i]);
    }
    digitalWrite(_csPin, HIGH);
}
