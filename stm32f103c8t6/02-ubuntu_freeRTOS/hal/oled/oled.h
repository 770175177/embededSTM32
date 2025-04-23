#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "soft_i2c.h"

#define OLED_I2C_ADDR		(0x78)
#define OLED_I2C_WRITE_ADDR	(OLED_I2C_ADDR & 0xFE)
#define OLED_I2C_READ_ADDR	(OLED_I2C_ADDR | 0x1)

typedef enum _OLED_CMD_DATA {
    OLED_CMD = 0,   // 写命令
    OLED_DATA = 1,  // 写数据
} OLED_CMD_DATA;

typedef enum _OLED_COLOR {
    OLED_COLOR_NORMAL = 0,
    OLED_COLOR_REVERSE = 1,
} OLED_COLOR;

typedef enum _OLED_ROTATE {
    OLED_ROTATE_NORMAL = 0,
    OLED_ROTATE_180_DEGREES = 1,
} OLED_ROTATE;

typedef enum _OLED_SSD1306_CMD {
    OLED_OFF = 0xAE,
    OLED_ON = 0xAF,
    OLED_SET_DISPLAY_ENTIRE_PIX_OFF = 0xA4, // 正常显示内容
    OLED_SET_DISPLAY_ENTIRE_PIX_ON = 0xA5,  // 显示所有像素
    OLED_SET_DISPLAY_NORMAL = 0xA6,         // 正常显示
    OLED_SET_DISPLAY_COLOR_REVERSE = 0xA7,  // 反色显示
    OLED_SET_MULTIPLEX_RATION = 0xA8,       // 设置分辨率，1 ~ 64
    OLED_SET_DISPLAY_RAM_OFFSET = 0xD3,     // 设置显示的偏移量，0x00 ~ 0x3F
    OLED_SET_MAPPING_RAM_START_LINE = 0x40, // 设置显示起始行地址, this + (0 ~ 64)
    OLED_SET_VCOMH_DESELECT_LEVEL = 0xDB,   // 设置Vcomh取消选通电平
    OLED_SET_CHARGE_PUMP_SWITCH = 0x8D,     // 电荷泵开关，后跟参数 0x10-关闭，0x14-开启
    OLED_SET_CONTRAST_RATIO = 0x81,         // 对比度，后跟参数 0x00 ~ 0xFF，越大屏幕越亮
    OLED_SET_COLUMN_MAPPING_REVERSE = 0xA0, // 左右反置
    OLED_SET_COLUMN_MAPPING_NORMAL = 0xA1,  // 左右正常
    OLED_SET_ROW_SCAN_REVERSE = 0xC0,       // 上下反置
    OLED_SET_ROW_SCAN_NORMAL = 0xC8,        // 上下正常
    OLED_SET_REFRESH_RATIO = 0xD5,          // 设置显示时钟分频比和振荡器频率，它决定了屏幕的刷新率以及数据传输的速度
    OLED_SET_PRECHARGE_PERIOD = 0xD9,       // 设置预充电周期，高4bits表示预充电周期，低4bits表示
    OLED_SET_COM_PINS_HARDWARE_CFG = 0xDA,
    OLED_SET_PAGE_0 = 0xB0,                 // 设置页0地址，低三位表示要设置的页
    OLED_SET_COM_OUTPUT_SCAN_DIR = 0xB8,    // 设置COM输出扫描方向，0xB8 ~ 0xBF 
    OLED_SET_COL0_LOW4_BITS = 0x00,         // 设置行0地址低4位
    OLED_SET_COL0_HIGH4_BITS = 0x10,        // 设置行0地址高4位
    OLED_SET_ADDRESS_MODE = 0x20,           // 支持3种地址模式，后跟设置的模式：
                                            //      0x00-水平地址模式（列++ -> page++），1-使用21h设置列起始与列终止地址，2-使用22h设置行起始与行终止地址
                                            //      0x01-垂直地址模式(page++ -> 列++) ，同水平地址模式的设置
                                            //      0x02-页地址模式（列++，page不变），1-先设置页地址，2-再设置列起始地址
} OLED_SSD1306_CMD;

typedef enum _OLED_SSD1306_PARAM_DEFAULT {
    OLED_PARAM_CONTRAST_RATIO = 0xCF,       // 对比度
    OLED_PARAM_MULTIPLEX_RATION = 0x3F,     // 分辨率 64
    OLED_PARAM_DISPLAY_RAM_OFFSET = 0x00,
    OLED_PARAM_REFRESH_RATIO = 0x80,        // 刷新率 100 帧/秒
    OLED_PARAM_PRECHARGE_PERIOD = 0xF1,     // 预充电 15 clocks & discharge 1 clock
    OLED_PARAM_HARDWARE_CFG = 0x12,
    OLED_PARAM_VCOMH_DESELECT_LEVEL = 0x40,
    OLED_PARAM_ADDRESS_MODE_PAGE = 0x00,
    OLED_PARAM_ADDRESS_MODE_HORIZENTAL = 0x01,
    OLED_PARAM_ADDRESS_MODE_VERTICAL = 0x02,
    OLED_PARAM_CHARGE_PUMP_OFF = 0x10,
    OLED_PARAM_CHARGE_PUMP_ON = 0x14,
} OLED_SSD1306_PARAM_DEFAULT;

typedef enum _OLED_FONT_SIZE {
    OLED_FONT_SIZE_SMALL = 12,
    OLED_FONT_SIZE_MIDDLE = 16,
    OLED_FONT_SIZE_BIG = 24,
} OLED_FONT_SIZE;

#define OLED_X_Y_AXIS(_x, _y)               8 * (_x), OLED_FONT_SIZE_SMALL * (_y)
#define OLED_X_Y_AXIS_S(_x, _y)             8 * (_x), OLED_FONT_SIZE_SMALL * (_y), OLED_FONT_SIZE_SMALL
#define OLED_X_Y_AXIS_M(_x, _y)             8 * (_x), OLED_FONT_SIZE_MIDDLE * (_y), OLED_FONT_SIZE_MIDDLE
#define OLED_X_Y_AXIS_B(_x, _y)             8 * (_x), OLED_FONT_SIZE_BIG * (_y), OLED_FONT_SIZE_BIG

#define OLED_SET_PAGE(_x)                   (OLED_SET_PAGE_0 | ((_x) & 0x7))            // 行范围 0 ~ 7
#define OLED_SET_COLUMN_LOW4_BITS(_x)       (OLED_SET_COL0_LOW4_BITS | ((_x) & 0xF))    // 列地址范围 0 ~ 127
#define OLED_SET_COLUMN_HIGH4_BITS(_x)      (OLED_SET_COL0_HIGH4_BITS | (((_x) >> 4) & 0xF))
#define OLED_SET_DISPALY_START_LINE(_x)     (OLED_SET_VCOM_START_LINE + (_x))           // 0 ~ 64

extern uint8_t *oled_pgram;
extern uint8_t OLED_GRAM_ROW_NUM;
extern uint8_t OLED_GRAM_COLUMN_NUM;

static void oled_write_byte(uint8_t data, uint8_t mode);
static inline void oled_write_cmd(uint8_t cmd);
static inline void oled_write_data(uint8_t data);
/* oled 控制函数 */
void oled_init(void);
void oled_display_on(void);
void oled_display_off(void);
void oled_color_switch(OLED_COLOR color);
void oled_display_rotate(OLED_ROTATE degree);
void oled_display_refresh(void);
void oled_display_clear(void);
/*** oled 显示函数
 * x: 0 ~ 127	------> x
 * y: 0 ~ 63	| y
 ***/
void oled_draw_point(uint8_t x, uint8_t y);
void oled_clear_point(uint8_t x, uint8_t y);
void oled_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void oled_draw_circle(uint8_t x, uint8_t y, uint8_t r);
void oled_show_char(uint8_t x, uint8_t y, uint8_t size1, uint8_t chr);
void oled_show_string(uint8_t x, uint8_t y, uint8_t size1, uint8_t *chr);
void oled_show_num(uint8_t x, uint8_t y, uint8_t size1, int16_t num, uint8_t len);
void oled_show_float(uint8_t x, uint8_t y, uint8_t size1, float fnum, uint8_t len);

#endif
