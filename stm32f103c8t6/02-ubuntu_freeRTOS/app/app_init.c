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

    delay_init();
    led_init();       		// PC13
    uart_init(115200);
	tim1_pwm_init(899, 0);	// 不分频，pwm频率 = 72000 / (899 + 1) = 80KHz

	usart_printf("\r\nMy FreeRTOS Project\r\n");
	usart_printf("My FreeRTOS Hardware Init Ok!\r\n");
}