// algorithms/spirit_calculator.c
#include "spirit_calculator.h"

#define BODY_WEIGHT_COEFF  0.6f
#define MIND_FOCUS_COEFF   0.4f

float calculate_spirit_value(uint32_t heart_rate, float activity_level) {
    // 基础灵力 = 体修系数 × 心率能量 + 法修系数 × 运动强度
    float body_energy = BODY_WEIGHT_COEFF * (heart_rate * 0.8f);
    float mind_energy = MIND_FOCUS_COEFF * (activity_level * 1.2f);
    return body_energy + mind_energy;
}