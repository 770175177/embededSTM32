#ifndef __LED_H__
#define	__LED_H__

#include "stm32f10x.h"

typedef enum {
    LED_OFF =   0,
    LED_ON =    1
} LED_STATUS;

void led_init(void);
void led_switch();
void led_light(LED_STATUS light);
unsigned char led_status(void);

#endif /* __LED_H__ */
