#include "led.h"

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void led_switch(void)
{
        if (led_status()) {
                GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        } else {
                GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }
}

void led_light(LED_STATUS light)
{
        if (light) {
                GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        } else {
                GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }
}

unsigned char led_status(void)
{
        unsigned char status;
        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        status = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
        led_init();

        return status;
}
