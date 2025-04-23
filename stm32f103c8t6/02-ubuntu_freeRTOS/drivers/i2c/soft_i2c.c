#include "soft_i2c.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void i2c_sda_dir(I2C_SDA_DIR_T out_in);
static uint8_t i2c_start(void);
static void i2c_stop(void);
static void i2c_ack(void);
static void i2c_nak(void);

void i2c_init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	   
	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	I2C_SCL(1);
	I2C_SDA(1);
}

void i2c_sda_dir(I2C_SDA_DIR_T out_in)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
	if (out_in == I2C_SDA_IN)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*----------------------- signal function ---------------------------*/

/* *** 
 * SCL: ---------____
 * SDA: ----_________
 * ***/
static uint8_t i2c_start(void)
{
	SDA_OUT();
	I2C_SDA(1);
	if (!READ_SDA())
		return I2C_STAT_OCUPPYED;
	I2C_SCL(1);
	delay_us(5);
 	I2C_SDA(0);
	delay_us(5);
	I2C_SCL(0);

	return I2C_STAT_OK;
}	  

/* *** 
 * SCL: ---------
 * SDA: _____----
 * ***/
static void i2c_stop(void)
{
	I2C_SCL(0);
	SDA_OUT();
	I2C_SDA(0);
	delay_us(5);
	I2C_SCL(1);
 	delay_us(5);
	I2C_SDA(1);
	delay_us(1);
}

/* *** 
 * ACK: return ACK
 * NAK: return NAK
 * ***/
static uint8_t i2c_wait_ack(void)
{
	uint8_t wait_times = 0;

	SDA_IN();
	delay_us(1);
	I2C_SCL(1);
	delay_us(1);	 
	while(READ_SDA()) {
		if(++wait_times > 250) {
			i2c_stop();
			return I2C_STAT_NAK;
		}
	}
	I2C_SCL(0);

	return I2C_STAT_ACK;
} 

/* *** 
 * SCL: ____----____
 * SDA: ____________
 * ***/
static void i2c_ack(void)
{
	I2C_SCL(0);
	SDA_OUT();
	I2C_SDA(0);
	delay_us(1);
	I2C_SCL(1);
	delay_us(1);
	I2C_SCL(0);
}

/* *** 
 * SCL: ____----____
 * SDA: ------------
 * ***/
static void i2c_nak(void)
{
	I2C_SCL(0);
	SDA_OUT();
	I2C_SDA(1);
	delay_us(1);
	I2C_SCL(1);
	delay_us(1);
	I2C_SCL(0);
}

/*----------------------- byte function ---------------------------*/

static uint8_t i2c_write_byte(uint8_t txd)
{
    uint8_t t;

	SDA_OUT();
    I2C_SCL(0);
    for(t = 0; t < 8; t++) {
		I2C_SDA((txd & 0x80) >> 7);
        txd <<= 1;
		delay_us(1);
		I2C_SCL(1);
		delay_us(1);
		I2C_SCL(0);
		delay_us(1);
    }

	return i2c_wait_ack();
}

static uint8_t i2c_read_byte(I2C_STAT_T ack)
{
	unsigned char i, receive = 0;

	SDA_IN();
    for(i = 0; i < 8; i++) {
        I2C_SCL(0);
        delay_us(2);
		I2C_SCL(1);
        receive <<= 1;
        if(READ_SDA())
			receive++;
		delay_us(2);
    }
    if (ack)
        i2c_ack();
    else
        i2c_nak();

    return receive;
}

/*----------------------- byte function ---------------------------*/

uint8_t i2c_transfer(uint16_t wlen, uint16_t rlen, uint8_t *data)
{
	int ret = 0;
	int i = 0;

	if (wlen < 1 || !data)
		return I2C_STAT_ERR_PARAM;

    if (ret = i2c_start())
        return ret;
	if (ret = i2c_write_byte(data[i]))
		return I2C_STAT_WADDR_NAK;
	while(++i < wlen)
		if (ret = i2c_write_byte(data[i]))
			return I2C_STAT_WDATA_NAK;
	i = 0;
	if ((wlen > 1) && (rlen > 0)) {
		if (ret = i2c_start())
			return I2C_STAT_RESTART_NAK;
		if (ret = i2c_write_byte(data[i] | I2C_ADDR_R_BIT))
			return I2C_STAT_RADDR_NAK;
		data[i] = data[i] | I2C_ADDR_R_BIT;
	}
	while(i++ < rlen) {
		if (i == rlen)
			data[i] = i2c_read_byte(I2C_STAT_NAK);
		else
			data[i] = i2c_read_byte(I2C_STAT_ACK);
	}
    i2c_stop();

    return I2C_STAT_OK;
}
