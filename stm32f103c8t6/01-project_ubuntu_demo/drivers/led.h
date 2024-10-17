#ifndef __LED_H__
#define	__LED_H__

#include "stm32f10x.h"
#include <stdio.h>

typedef enum {
    LED_OFF =   0,
    LED_ON =    1
} LED_STATUS;

void led_init(void);
void led_switch(LED_STATUS light);

#endif /* __LED_H__ */
