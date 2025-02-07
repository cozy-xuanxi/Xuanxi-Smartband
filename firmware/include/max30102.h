#ifndef MAX30102_H
#define MAX30102_H

#include <stdint.h>
#include "hi_i2c.h"


#define MAX30102_I2C_ADDR    0x57
#define MAX30102_REG_FIFO    0x05

// 初始化MAX30102
int max30102_init(i2c_idx i2c_port);

// 读取心率与血氧原始数据
void max30102_read_fifo(uint32_t *red, uint32_t *ir);

#endif