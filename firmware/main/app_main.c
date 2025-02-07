// main/app_main.c
#include <stdio.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "max30102.h"
#include "spirit_calculator.h"
#include "ssd1306.h"  // 假设已实现OLED驱动

static void xuanxi_task(void *arg) {
    (void)arg;
    
    // 初始化传感器
    if (max30102_init(I2C0) != 0) {
        printf("[玄息核心] 气血感应阵启动失败!\n");
        return;
    }
    ssd1306_init(); // 初始化OLED
    
    while (1) {
        uint32_t red, ir;
        max30102_read_fifo(&red, &ir);
        
        // 简化的心率计算（实际需PPG算法）
        uint32_t heart_rate = red / 1000; 
        float activity = (ir - red) * 0.01f;
        
        // 计算灵力值
        float spirit = calculate_spirit_value(heart_rate, activity);
        
        // OLED显示
        char buf[32];
        snprintf(buf, sizeof(buf), "灵力值: %.1f", spirit);
        ssd1306_show_string(0, 0, buf);
        
        osDelay(1000); // 鸿蒙OS延时函数
    }
}

// 鸿蒙OS应用入口
void xuanxi_main(void) {
    osThreadAttr_t attr = {.name = "xuanxi_task", .stack_size = 4096};
    if (osThreadNew(xuanxi_task, NULL, &attr) == NULL) {
        printf("[玄息核心] 心法运转失败!\n");
    }
}

SYS_RUN(xuanxi_main); // 注册为系统任务