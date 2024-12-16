#ifndef __SPI_1_H__
#define __SPI_1_H__
#include "sys.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"

/* GPIOA */
#define SPI1_NSS_PIN        GPIO_Pin_4
#define SPI1_SCK_PIN        GPIO_Pin_5
#define SPI1_MISO_PIN       GPIO_Pin_6
#define SPI1_MOST_PIN       GPIO_Pin_7

#define spi1_nss_set(level)                 \
do {                                        \
    if (level)                              \
        GPIO_SetBits(GPIOA, SPI1_NSS_PIN);  \
    else                                    \
        GPIO_ResetBits(GPIOA, SPI1_NSS_PIN); \
} while(0)

enum __LEVEL {
    LOW     = 0x0,
    HIGH    = 0x1,
};

void spi1_init(void);

/*********************************************************
 * SPI_BaudRatePrescaler_2   2   div (SPI 36M@sys 72M)
 * SPI_BaudRatePrescaler_8   8   div (SPI 9M@sys 72M)
 * SPI_BaudRatePrescaler_16  16  div (SPI 4.5M@sys 72M)
 * SPI_BaudRatePrescaler_256 256 div (SPI 281.25K@sys 72M)
**********************************************************/
void spi1_set_speed(u8 speed);

/*********************************************************
 * SPI read write a byte
 * tx_data: data to send
 * return: data to read
**********************************************************/
int8_t spi1_write_read_byte(u8 tx_data, u8 *rx_data);

#endif      /* __SPI_1_H__ */

