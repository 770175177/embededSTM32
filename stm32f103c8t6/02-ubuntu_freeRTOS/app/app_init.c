#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "soft_i2c.h"
#include "oled.h"
#include "app_init.h"
#include "log_module.h"

uint32_t error_flag = 0xFFFFFFFF;
uint32_t warn_flag = 0x0;
uint32_t print_flag = 0x0;
uint32_t debug_flag = 0x0;

void app_init(void)
{
	//将全部优先级设为抢占优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	uart_init(115200);
    delay_init();
	i2c_init();
    led_init();       		// PC13
	oled_init();
	
	tim4_pwm_init(PWM4_PER_MAX);

	print_flag = PRINT_MODULE_TASK_MOTOR |
				PRINT_MODULE_OLED;

	usart_printf("\n\r\n\r");
	usart_printf("##################################\n\r");
	usart_printf("##                              ##\n\r");
	usart_printf("##      My FreeRTOS Project     ##\n\r");
	usart_printf("##################################\n\r");
	usart_printf("Hardware Init Ok!\n\r");
}
