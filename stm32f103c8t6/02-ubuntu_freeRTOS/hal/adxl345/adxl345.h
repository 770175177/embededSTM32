#ifndef __ADXL345_H__
#define __ADXL345_H__
#include "spi.h"

#define DEBUG_ADXL345

#define ADXL345_DEVICEID    0xE5

typedef enum __adxl345_cmd {
    ADXL_DEVICEID   = 0x00,
    ADXL_RESVED     = 0x01,
    ADXL_THRESH_TAP = 0x1D,
    ADXL_OFFSX      = 0x1E,
    ADXL_OFFSY      = 0x1F,
    ADXL_OFFSZ      = 0x20,
    ADXL_DUR_TAP    = 0x21,
    ADXL_LATENT_TAP = 0x22,
    ADXL_WIN_TAP    = 0x23,
    ADXL_THRESH_ACT = 0x24,
    ADXL_THRESH_INA = 0x25,
    ADXL_TIME_INACT = 0x26,
    ADXL_ACT_INA_EN = 0x27,
    ADXL_THRESH_FF  = 0x28,
    ADXL_TIME_FF    = 0x29,
    ADXL_TAP_AXES   = 0x2A,
    ADXL_ACTTAP_STA = 0x2B,
    ADXL_BW_RATE    = 0x2C,     // 数据采集速度，|[D7:D5]==0|D4=1 低功耗|[D3:D0]=速率| 默认为0xa, 100HZ|
    ADXL_PWR_CTRL   = 0x2D,     // 控制，|D5=1链接|D4=1静止时休眠|D3=1测量|D2=1休眠|[D1:D0]休眠下的读取频率|
    ADXL_INT_ENABLE = 0x2E,     // 中断，|D7=数据可用|D6=1单击|D5=1双击|D4=1活动|D3=1非活动|D2free fall|D1=1水位|D0=1覆盖|
    ADXL_INT_MAP    = 0x2F,     // 中断映射，以上中断=0映射到INT1引脚，=1映射到INT2引脚
    ADXL_INT_SOURCE = 0x30,     // 中断源，=1对应有中断发生
    ADXL_DAT_FORMAT = 0x31,     // 控制数据显示，|D7=1自测|D6=1设置3线spi|D5=1中断低有效|D4==0|D3=1全分辨率|D2=1左对齐|[D1:D0]=g范围|
    ADXL_DAT_X0     = 0x32,
    ADXL_DAT_X1     = 0x33,
    ADXL_DAT_Y0     = 0x34,
    ADXL_DAT_Y1     = 0x35,
    ADXL_DAT_Z0     = 0x36,
    ADXL_DAT_Z1     = 0x37,
    ADXL_FIFO_CTRL  = 0x38,
    ADXL_FIFO_STAT  = 0x39,
} adxl345_cmd;

int8_t adxl345_init(void);

int8_t adxl345_write_read_bytes(u8 txrx_data[], uint8_t length);

void adxl345_write(uint8_t addr, uint8_t value);

uint8_t adxl345_read(uint8_t addr);

uint16_t adxl345_read_burst(uint8_t addr);

void adxl345_read_xyz_axis(uint16_t *xAxis, uint16_t *yAxis, uint16_t *zAxis);

#endif      /* __ADXL345_H__ */

