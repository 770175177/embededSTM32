#include "key.h"

void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = KEY0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // pull up input
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // pull up input
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t key_scan(void)
{
	static uint8_t pressedTick = 0;

	if(KEY0_VAL() == KEY_DOWN || KEY1_VAL() == KEY_DOWN)
		pressedTick++;
	else
		pressedTick = 0;

	if(pressedTick == 2) {
		if(KEY0_VAL() == KEY_DOWN)
			return KEY0_DOWN;
		else if(KEY1_VAL() == KEY_DOWN)
			return KEY1_UP;
	}

	return KEY_INVALID;
}

