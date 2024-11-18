#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "app_tasks.h"
 
void task_main(void *pvParameters)
{
	TickType_t currentTickCount, TickCount;
	TickType_t lastTickCount, lastTimestampCount;

	usart_printf("\r\nMain Task Create\r\n");

	taskENTER_CRITICAL();
	create_subtasks();
	taskEXIT_CRITICAL();

	lastTickCount = xTaskGetTickCount();
	lastTimestampCount = lastTickCount;

	while(1) {
		currentTickCount = xTaskGetTickCount();

		TickCount = currentTickCount - lastTickCount;
		if (TickCount > pdMS_TO_TICKS(500)) {
			lastTickCount = currentTickCount;
			led_switch();
		}

		TickCount = currentTickCount - lastTimestampCount;
		if (TickCount > pdMS_TO_TICKS(5000)) {
			lastTimestampCount = currentTickCount;
			usart_printf("\r\n[%d] Main Task is running",
				currentTickCount / configTICK_RATE_HZ);
		}

		vTaskDelay(10);
	}
}

void subtask1_sensors(void *pvParameters)
{
	usart_printf("\r\nSensors Task Create\r\n");

	while(1) {

		vTaskDelay(10);
	}
}

void subtask2_motors(void *pvParameters)
{
	TickType_t currentTickCount, TickCount;
	TickType_t lastTickCount, lastTimestampCount;

	lastTickCount = xTaskGetTickCount();
	lastTimestampCount = lastTickCount;

	usart_printf("\r\nMotors Task Create\r\n");
	tim1_pwm_set_duty(800);

	while(1) {
		currentTickCount = xTaskGetTickCount();

		TickCount = currentTickCount - lastTickCount;
		if (TickCount > pdMS_TO_TICKS(1000)) {
			lastTickCount = currentTickCount;
			usart_printf("\r\n[%d] Motors Task is running",
				currentTickCount / configTICK_RATE_HZ);
		}
	}
}


