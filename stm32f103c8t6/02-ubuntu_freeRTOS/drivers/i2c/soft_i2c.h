#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

#define I2C_SCL_PIN     GPIO_Pin_10
#define I2C_SDA_PIN     GPIO_Pin_11

#define I2C_GPIO_OUT(pin, _x) do { \
        if(_x) \
            GPIO_SetBits(GPIOB, pin); \
        else \
            GPIO_ResetBits(GPIOB, pin); \
    } while(0)

#define I2C_SCL(x)      I2C_GPIO_OUT(I2C_SCL_PIN, x)
#define I2C_SDA(x)      I2C_GPIO_OUT(I2C_SDA_PIN, x)
#define READ_SDA()      GPIO_ReadInputDataBit(GPIOB, I2C_SDA_PIN)

#define I2C_ADDR_R_BIT  (0x1)

typedef enum __I2C_SDA_DIR {
    I2C_SDA_OUT = 0,
    I2C_SDA_IN = 1,
} I2C_SDA_DIR_T;

#define SDA_IN()        i2c_sda_dir(I2C_SDA_IN)
#define SDA_OUT()       i2c_sda_dir(I2C_SDA_OUT)

typedef enum __I2C_STAT {
    I2C_STAT_OK = 0,
    I2C_STAT_ACK = 0,
    I2C_STAT_NAK = 1,
    I2C_STAT_WADDR_NAK = 2,
    I2C_STAT_RADDR_NAK = 3,
    I2C_STAT_WDATA_NAK = 4,
    I2C_STAT_RDATA_NAK = 5,
    I2C_STAT_OCUPPYED = 6,
    I2C_STAT_RESTART_NAK = 7,
    I2C_STAT_ERR_PARAM = 8,
    I2C_STAT_MAX,
} I2C_STAT_T;

void i2c_init(void);
void i2c_sda_dir(I2C_SDA_DIR_T dir);

uint8_t i2c_transfer(uint16_t wlen, uint16_t rlen, uint8_t *data);

#endif
















