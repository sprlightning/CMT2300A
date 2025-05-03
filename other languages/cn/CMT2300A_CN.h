#ifndef CMT2300A_CN_H
#define CMT2300A_CN_H

#include <Arduino.h>
#include <SPI.h>

// thanks to prj: https://github.com/Izzi-bro/CMT2300A, it is very nice!
// 非常感谢项目：https://github.com/Izzi-bro/CMT2300A，这是我见过的最简洁的关于cmt2300a的项目，它明确说明了如何操作这款芯片，包括设置功率、频率、数据收发等。我将它翻译成了中文，除了注释语言变更，其余无变化。

class CMT2300A {
public:
    // 类构造函数
    CMT2300A(uint8_t csPin);

    // 设备初始化
    void begin();

    // 设置频率
    void setFrequency(uint32_t freq);

    // 设置带宽
    void setBandwidth(uint8_t bandwidth);

    // 设置发射功率
    void setPower(uint8_t power);

    // 设置扩频因子（SF）
    void setSpreadingFactor(uint8_t sf);

    // 设置编码率（CR）
    void setCodingRate(uint8_t rate);

    // 设置数据包长度
    void setPacketLength(uint8_t length);

    // 设置LNA增益
    void setLNA(uint8_t gain);

    // 设置发射滤波器带宽
    void setTXFilterBandwidth(uint8_t bandwidth);

    // 设置接收滤波器带宽
    void setRXFilterBandwidth(uint8_t bandwidth);

    // 设置64位设备地址
    void setAddress(uint64_t address);

    // 设置工作模式
    void setMode(uint8_t mode);

    // 配置管道参数（频率和带宽）
    void setPipe(uint8_t pipe, uint32_t freq, uint8_t bandwidth);

    // 设置管道模式
    void setPipeMode(uint8_t pipe, uint8_t mode);

    // 发送数据
    void sendMessage(uint8_t* data, uint8_t length);

    // 接收数据
    void receiveMessage(uint8_t* data, uint8_t* length);

private:
    uint8_t _csPin;

    // 寄存器写入
    void writeRegister(uint8_t reg, uint8_t value);

    // 寄存器读取
    uint8_t readRegister(uint8_t reg);

    // SPI数据传输
    void spiTransfer(uint8_t* txBuf, uint8_t* rxBuf, size_t len);

    // 寄存器定义
    const uint8_t REG_OP_MODE = 0x01;          // 工作模式寄存器
    const uint8_t REG_FREQ_MSB = 0x06;         // 频率高位
    const uint8_t REG_FREQ_MID = 0x07;         // 频率中位
    const uint8_t REG_FREQ_LSB = 0x08;         // 频率低位
    const uint8_t REG_BW = 0x09;               // 带宽设置
    const uint8_t REG_POWER = 0x0C;            // 发射功率
    const uint8_t REG_SF = 0x0D;               // 扩频因子
    const uint8_t REG_CR = 0x0E;               // 编码率
    const uint8_t REG_PAC = 0x0F;              // 数据包长度
    const uint8_t REG_LNA = 0x13;              // LNA增益
    const uint8_t REG_TX_FILTER_BW = 0x14;    // 发射滤波器带宽
    const uint8_t REG_RX_FILTER_BW = 0x15;    // 接收滤波器带宽
    const uint8_t REG_ADDRESS_MSB = 0x1A;     // 地址高位
    const uint8_t REG_ADDRESS_LSB = 0x1B;     // 地址低位
    const uint8_t REG_MODE = 0x1C;            // 工作模式
    const uint8_t REG_PIPE0 = 0x1E;           // 管道0配置
    const uint8_t REG_PIPE1 = 0x1F;           // 管道1配置
    const uint8_t REG_PIPE0_MODE = 0x20;     // 管道0模式
    const uint8_t REG_PIPE1_MODE = 0x21;     // 管道1模式
    const uint8_t REG_FIFO = 0x22;           // FIFO数据寄存器

    // 工作模式定义
    static const uint8_t MODE_SLEEP = 0x00;  // 睡眠模式
    static const uint8_t MODE_TX = 0x01;     // 发射模式
    static const uint8_t MODE_RX = 0x02;     // 接收模式

    // 管道模式定义
    static const uint8_t PIPE_MODE_TX = 0x01;  // 发射管道
    static const uint8_t PIPE_MODE_RX = 0x02;  // 接收管道

    // 带宽参数定义
    static const uint8_t BW_7_8KHz = 0x00;    // 7.8kHz
    static const uint8_t BW_10_4KHz = 0x01;  // 10.4kHz
    static const uint8_t BW_15_6KHz = 0x02;  // 15.6kHz
    static const uint8_t BW_20_8KHz = 0x03;  // 20.8kHz
    static const uint8_t BW_31_2KHz = 0x04;  // 31.2kHz
    static const uint8_t BW_41_7KHz = 0x05;  // 41.7kHz
    static const uint8_t BW_62_5KHz = 0x06;  // 62.5kHz
    static const uint8_t BW_125KHz = 0x07;   // 125kHz

    // 编码率定义
    static const uint8_t CR_4_5 = 0x01;      // 4/5
    static const uint8_t CR_4_6 = 0x02;      // 4/6
    static const uint8_t CR_4_7 = 0x03;      // 4/7
    static const uint8_t CR_4_8 = 0x04;      // 4/8
};

#endif
