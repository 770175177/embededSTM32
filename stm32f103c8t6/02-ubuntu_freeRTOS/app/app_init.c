#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "app_init.h"
#include "log_module.h"

uint32_t print_flag = 0x0;

void app_init(void)
{
	//将全部优先级设为抢占优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	uart_init(115200);
    delay_init();
    led_init();       		// PC13
	
	tim4_pwm_init(PWM4_PER_MAX);

	print_flag = PRINT_MODULE_TASK_MOTOR;

	usart_printf("\r\n\r\n");
	usart_printf("##################################\r\n");
	usart_printf("##                              ##\r\n");
	usart_printf("##      My FreeRTOS Project     ##\r\n");
	usart_printf("##################################\r\n");
	usart_printf("Hardware Init Ok!\r\n");
}
