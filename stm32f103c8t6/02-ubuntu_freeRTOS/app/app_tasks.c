#include <string.h>
#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "app_tasks.h"
 
void main_task(void *pvParameters)
{
	u8 led = LED_OFF;

	while(1)
	{
    	led_switch(led);
		vTaskDelay(200);
		led = !led;
		led_switch(led);
		vTaskDelay(200);
	}
}
