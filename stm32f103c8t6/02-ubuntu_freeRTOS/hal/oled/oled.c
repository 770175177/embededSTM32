#include "oled.h"
#include "oledfont.h"
#include "delay.h"
#include "log_module.h"

// OLED 的显存
// 驱动 IC:  SSD1306
// 点阵大小: 64(行, 1 COM 控制8行) * 128(列)
// 存放的格式如下:
// 		[0] 0 1 2 3 ... 127
// 		[1] 0 1 2 3 ... 127
// 		[2] 0 1 2 3 ... 127
// 		[3] 0 1 2 3 ... 127
// 		[4] 0 1 2 3 ... 127
// 		[5] 0 1 2 3 ... 127
// 		[6] 0 1 2 3 ... 127
// 		[7] 0 1 2 3 ... 127
static uint8_t OLED_GRAM[128][8];
uint8_t *oled_pgram = (uint8_t *)OLED_GRAM;
uint8_t OLED_GRAM_ROW_NUM = sizeof(OLED_GRAM[0]);
uint8_t OLED_ROWS_PIX_NUM = (sizeof(OLED_GRAM[0]) * 8);
uint8_t OLED_GRAM_COLUMN_NUM = sizeof(OLED_GRAM) / sizeof(OLED_GRAM[0]);

/* ------------------ inner functions -------------------- */
static void oled_write_byte(uint8_t data, uint8_t mode)
{
	uint8_t ret = 0;
	uint8_t buf[3] = {OLED_I2C_WRITE_ADDR, 0x00, data};

	if (mode == OLED_DATA)
		buf[1] = 0x40;
	ret = i2c_transfer(3, 0, buf);
	if (ret)
		OLED_ERROR("write data 0x%x error, ret %d\r\n", data, ret);
}

static inline void oled_write_cmd(uint8_t cmd)
{
	oled_write_byte(cmd, OLED_CMD);
}

static inline void oled_write_data(uint8_t data)
{
	oled_write_byte(data, OLED_DATA);
}

/* ------------------ outer control functions -------------------- */
void oled_init(void)
{
	oled_write_cmd(OLED_OFF);
	oled_write_cmd(OLED_SET_COLUMN_LOW4_BITS(0));
	oled_write_cmd(OLED_SET_COLUMN_HIGH4_BITS(0));
	oled_write_cmd(OLED_SET_MAPPING_RAM_START_LINE);
	oled_write_cmd(OLED_SET_CONTRAST_RATIO);		// 设置对比度 0x00 ~ 0xFF
	oled_write_cmd(OLED_PARAM_CONTRAST_RATIO);
	oled_write_cmd(OLED_SET_COLUMN_MAPPING_NORMAL);
	oled_write_cmd(OLED_SET_ROW_SCAN_NORMAL);
	oled_write_cmd(OLED_SET_DISPLAY_ENTIRE_PIX_OFF);
	oled_write_cmd(OLED_SET_DISPLAY_NORMAL);
	oled_write_cmd(OLED_SET_MULTIPLEX_RATION);
	oled_write_cmd(OLED_PARAM_MULTIPLEX_RATION);
	oled_write_cmd(OLED_SET_DISPLAY_RAM_OFFSET);
	oled_write_cmd(OLED_PARAM_DISPLAY_RAM_OFFSET);
	oled_write_cmd(OLED_SET_REFRESH_RATIO);
	oled_write_cmd(OLED_PARAM_REFRESH_RATIO);
	oled_write_cmd(OLED_SET_PRECHARGE_PERIOD);
	oled_write_cmd(OLED_PARAM_PRECHARGE_PERIOD);
	oled_write_cmd(OLED_SET_COM_PINS_HARDWARE_CFG);
	oled_write_cmd(OLED_PARAM_HARDWARE_CFG);
	oled_write_cmd(OLED_SET_VCOMH_DESELECT_LEVEL);
	oled_write_cmd(OLED_PARAM_VCOMH_DESELECT_LEVEL);
	oled_write_cmd(OLED_SET_ADDRESS_MODE);
	oled_write_cmd(OLED_PARAM_ADDRESS_MODE_VERTICAL);
	oled_write_cmd(OLED_SET_CHARGE_PUMP_SWITCH);
	oled_write_cmd(OLED_PARAM_CHARGE_PUMP_ON);
	oled_write_cmd(OLED_ON);

	oled_display_rotate(OLED_ROTATE_180_DEGREES);
}

void oled_display_on(void)
{
	oled_write_cmd(OLED_SET_CHARGE_PUMP_SWITCH);// 电荷泵使能
	oled_write_cmd(OLED_PARAM_CHARGE_PUMP_ON);	// 开启电荷泵
	oled_write_cmd(OLED_ON);					// 点亮屏幕
}

void oled_display_off(void)
{
	oled_write_cmd(OLED_SET_CHARGE_PUMP_SWITCH);// 电荷泵使能
	oled_write_cmd(OLED_PARAM_CHARGE_PUMP_OFF);	// 关闭电荷泵
	oled_write_cmd(OLED_OFF);					// 关闭屏幕
}

void oled_color_switch(OLED_COLOR color)
{
	if (color == OLED_COLOR_REVERSE)
		oled_write_cmd(OLED_SET_DISPLAY_COLOR_REVERSE);
	else
		oled_write_cmd(OLED_SET_DISPLAY_NORMAL);
}

void oled_display_rotate(OLED_ROTATE degree)
{
	if (degree == OLED_ROTATE_180_DEGREES) {
		oled_write_cmd(OLED_SET_ROW_SCAN_REVERSE);
		oled_write_cmd(OLED_SET_COLUMN_MAPPING_REVERSE);
	} else {
		oled_write_cmd(OLED_SET_ROW_SCAN_NORMAL);
		oled_write_cmd(OLED_SET_COLUMN_MAPPING_NORMAL);
	}
}

void oled_display_refresh(void)
{
	uint8_t row, column;

	for (row = 0; row < OLED_GRAM_ROW_NUM; row++) {
		oled_write_cmd(OLED_SET_PAGE(row)); 			// set start row
		oled_write_cmd(OLED_SET_COLUMN_LOW4_BITS(0));	// set start column low 4 bits
		oled_write_cmd(OLED_SET_COLUMN_HIGH4_BITS(0));	// set start column high 4 bits
		for (column = 0; column < OLED_GRAM_COLUMN_NUM; column++)
			oled_write_data(OLED_GRAM[column][row]);
	}
}

void oled_display_clear(void)
{
	uint8_t row, column;

	for (row = 0; row < OLED_GRAM_ROW_NUM; row++)
	   for (column = 0; column < OLED_GRAM_COLUMN_NUM; column++)
			OLED_GRAM[column][row] = 0x00;

	oled_display_refresh();
}

/* ------------------ outer draw functions -------------------- */
/* x: 0 ~ 127		------> x
 * y: 0 ~ 63		| y
 */
void oled_draw_point(uint8_t x, uint8_t y)
{
	uint8_t com, mod, mask;

	com = y / OLED_GRAM_ROW_NUM;
	mod = y % OLED_GRAM_ROW_NUM;
	mask = 0x1 << mod;
	OLED_GRAM[x][com] |= mask;
}

void oled_clear_point(uint8_t x, uint8_t y)
{
	uint8_t com, mod, mask;

	com = y / OLED_GRAM_ROW_NUM;
	mod = y % OLED_GRAM_ROW_NUM;
	mask = 0x1 << mod;
	OLED_GRAM[x][com] &= ~mask;
}

/* 直线函数：y = kx + b
 * 已知两个点坐标，求直线方程
 */
void oled_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t i, max_x, min_x, max_y, min_y;
	int8_t k;

	min_x = x1 < x2 ? x1 : x2;
	max_x = x1 > x2 ? x1 : x2;
	min_y = y1 < y2 ? y1 : y2;
	max_y = y1 > y2 ? y1 : y2;

	if ((min_x < 0) || (max_x >= OLED_GRAM_COLUMN_NUM) || (min_y < 0) || (max_y >= OLED_ROWS_PIX_NUM)) {
		OLED_ERROR("oled draw line parameter error, (%d,%d)<--->(%d,%d)\r\n", x1, y1, x2, y2);
		return;
	}

	if (x1 == x2) {		// 竖线没有斜率。特俗处理
		for(i = min_y; i <= max_y; i++)
			oled_draw_point(min_x, i);
	} else {			// 斜线，k 表示斜率的 10 倍
		k = (y2 - y1) * 10 / (x2 - x1);
		if (x1 <= x2) {
			for (i = x1; i <= x2; i++)
				oled_draw_point(i, y1 + i * k / 10);
		} else {
			for (i = x1; i >= x2; i--)
				oled_draw_point(i, y1 + i * k / 10);
		}
	}
}

/* x, y 为圆心坐标
 * r 为圆的半径
 */
void oled_draw_circle(uint8_t x, uint8_t y, uint8_t r)
{
	int a, b, num;
    a = 0;
    b = r;

    while (2 * b * b >= r * r) {
        oled_draw_point(x + a, y - b);
        oled_draw_point(x - a, y - b);
        oled_draw_point(x - a, y + b);
        oled_draw_point(x + a, y + b);
 
        oled_draw_point(x + b, y + a);
        oled_draw_point(x + b, y - a);
        oled_draw_point(x - b, y - a);
        oled_draw_point(x - b, y + a);
        
        a++;
        num = (a * a + b * b) - r * r;	// 计算画的点到圆心的距离
        if(num > 0) {
            b--;
            a--;
        }
    }
}

/* ------------------ outer char functions -------------------- */
/* 显示一个字符
 * x: 0 ~ 127
 * y: 0 ~ 63
 * size: 字体大小，12/16/24
 */
void oled_show_char(uint8_t x, uint8_t y, uint8_t size1, uint8_t chr)
{
	uint8_t i, m, temp, size2, chr1;
	uint8_t y0 = y;

	size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2);
	chr1 = chr - ' ';
	for(i = 0; i < size2; i++) {
		if(size1 == OLED_FONT_SIZE_SMALL)
			temp = asc2_1206[chr1][i];
		else if(size1 == OLED_FONT_SIZE_MIDDLE)
			temp = asc2_1608[chr1][i];
		else if(size1 == OLED_FONT_SIZE_BIG)
        	temp = asc2_2412[chr1][i];
		else
			return;
		for (m = 0; m < 8; m++) {
			if(temp & 0x80)
				oled_draw_point(x, y);
			else
				oled_clear_point(x, y);
			temp <<= 1;
			y++;
			if((y - y0) == size1) {
				y = y0;
				x++;
				break;
			}
		}
	}
}

void oled_show_string(uint8_t x, uint8_t y, uint8_t size1, uint8_t *chr)
{
	while ((*chr >= ' ') && (*chr <= '~')) {
		oled_show_char(x, y, size1, *chr);
		x += size1 / 2;
		if (x > 128 - size1) {
			x = 0;
			y += 2;
		}
		chr++;
	}
}

// m ^ n
uint32_t oled_pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;

	while (n--)
	  result *= m;

	return result;
}

void oled_show_num(uint8_t x, uint8_t y, uint8_t size1, int16_t num, uint8_t len)
{
	uint8_t t = 0, temp = 0;

	if (num < 0) {
		oled_show_char(x + (size1 / 2) * t, y, size1, '-');
		num = 0 - num;
	} else {
		oled_show_char(x + (size1 / 2) * t, y, size1, ' ');
	}
	len++;
	for(t = 1; t < len; t++) {
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if(temp == 0)
			oled_show_char(x + (size1 / 2) * t, y, size1, '0');
		else
			oled_show_char(x + (size1 / 2) * t, y, size1, temp + '0');
	}
}

void oled_show_float(uint8_t x, uint8_t y, uint8_t size1, float fnum, uint8_t len)
{
	uint8_t t, temp;
	int32_t num = 0;
	len += 2;

	if (fnum < 0) {
		oled_show_char(x + (size1 / 2) * t, y, size1, '-');
		num = (int32_t)((-fnum) * 100);
	} else {
		oled_show_char(x + (size1 / 2) * t, y, size1, ' ');
		num = (int32_t)(fnum * 100);
	}

	for(t = 1; t <= len; t++) {
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if(temp == 0)
			oled_show_char(x + (size1 / 2) * t, y, size1, '0');
		else
			oled_show_char(x + (size1 / 2) * t, y, size1, temp + '0');
		if(t == len - 3) {
			oled_show_char(x + (size1 / 2) * (++t), y, size1, '.');
			len++;
		}
	}
}
