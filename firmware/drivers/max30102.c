// drivers/max30102.c
#include "max30102.h"

static i2c_idx max_i2c_port;

int max30102_init(i2c_idx i2c_port) {
    max_i2c_port = i2c_port;
    // I2C初始化（鸿蒙OS API）
    if (IoTI2cInit(max_i2c_port, 400000) != 0) {
        return -1; // 初始化失败
    }
    
    // 配置传感器模式（伪代码示例）
    uint8_t mode_cfg[] = {0x09, 0x03}; // 心率和血氧模式
    if (IoTI2cWrite(max_i2c_port, MAX30102_I2C_ADDR, mode_cfg, sizeof(mode_cfg)) != 0) {
        return -2; // 配置失败
    }
    return 0;
}

void max30102_read_fifo(uint32_t *red, uint32_t *ir) {
    uint8_t fifo_data[6];
    // 读取FIFO数据（伪代码示例）
    IoTI2cRead(max_i2c_port, MAX30102_I2C_ADDR, MAX30102_REG_FIFO, fifo_data, 6);
    
    // 解析红光（RED）和红外（IR）数据
    *red = (fifo_data[0] << 16) | (fifo_data[1] << 8) | fifo_data[2];
    *ir  = (fifo_data[3] << 16) | (fifo_data[4] << 8) | fifo_data[5];
}