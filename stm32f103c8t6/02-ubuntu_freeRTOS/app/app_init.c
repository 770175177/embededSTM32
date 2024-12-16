#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "app_init.h"

void app_init(void)
{
	//将全部优先级设为抢占优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	uart_init(115200);
    delay_init();
    led_init();       		// PC13
	tim4_pwm_init(PWM4_PER_MAX);

	usart_printf("\r\n");
	usart_printf("\r\n##################################");
	usart_printf("\r\n##                              ##");
	usart_printf("\r\n##      My FreeRTOS Project     ##");
	usart_printf("\r\n##################################");
	usart_printf("\r\nHardware Init Ok!");
}
