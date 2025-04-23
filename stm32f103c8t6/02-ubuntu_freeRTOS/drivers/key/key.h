#ifndef __KEY_H__
#define	__KEY_H__

#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define KEY_DOWN    0
#define KEY_UP      1

/* GPIOB */
#define KEY0_PIN    GPIO_Pin_0
#define KEY1_PIN    GPIO_Pin_1

enum __KEY {
    KEY_INVALID     = 0,
    KEY0_DOWN       = 1,
    KEY1_UP         = 2,
    KEY0_1_MENU     = 3,
    KEY_MAX,
};

#define KEY0_VAL()  GPIO_ReadInputDataBit(GPIOB, KEY0_PIN)
#define KEY1_VAL()  GPIO_ReadInputDataBit(GPIOB, KEY1_PIN)

void key_init(void);
uint8_t key_scan(void);

#endif  /* __KEY_H__ */