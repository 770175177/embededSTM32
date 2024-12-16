#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "adxl345.h"
#include "app_tasks.h"

void task_main(void *pvParameters)
{
	TickType_t currentTickCount, TickCount;
	TickType_t lastTickCount, lastTimestampCount;

	usart_printf("\r\nMain Task Create");

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
		if (TickCount > pdMS_TO_TICKS(10000)) {
			lastTimestampCount = currentTickCount;
			// usart_printf("\r\n[%d] Main Task is running",
			// 	currentTickCount / configTICK_RATE_HZ);
		}

		vTaskDelay(10);
	}
}

void subtask1_sensors(void *pvParameters)
{
	usart_printf("\r\nSensors Task Create");

	while(1) {

		vTaskDelay(100);
	}
}

void subtask2_motors(void *pvParameters)
{
	TickType_t currentTickCount, TickCount;
	TickType_t lastTickCount, lastTimestampCount;
	int16_t xAxis, yAxis, zAxis;

	adxl345_init();

	lastTickCount = xTaskGetTickCount();
	lastTimestampCount = lastTickCount;

	usart_printf("\r\nMotors Task Create");

	tim4_pwm_set_duty(PWM4_CH1, PWM4_PER_MAX);
	tim4_pwm_set_duty(PWM4_CH2, 0);
	tim4_pwm_set_duty(PWM4_CH3, PWM4_PER_MAX);
	tim4_pwm_set_duty(PWM4_CH4, 0);

	while(1) {
		currentTickCount = xTaskGetTickCount();
		adxl345_read_xyz_axis(&xAxis, &yAxis, &zAxis);

		TickCount = currentTickCount - lastTickCount;
		if (TickCount > pdMS_TO_TICKS(1000)) {
			lastTickCount = currentTickCount;

			usart_printf("\r\n[%d] Motors Task is running, X: %d, Y: %d, Z: %d",
				currentTickCount / configTICK_RATE_HZ, xAxis, yAxis, zAxis);
		}

		vTaskDelay(10);
	}
}


