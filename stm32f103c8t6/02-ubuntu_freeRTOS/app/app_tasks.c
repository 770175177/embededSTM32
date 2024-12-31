#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "pwm.h"
#include "adxl345.h"
#include "kalman.h"
#include "pid.h"
#include "car.h"
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
	kalman kfp, *pkfp = &kfp;
	pid_t pid, *ppid = &pid;
	int16_t xAxis, yAxis, zAxis, kxAxis;
	int32_t pidOut = 0;

	adxl345_init();
	kalman_init(pkfp);
	pid_init(ppid, 0, PWM4_PER_MAX/3, PWM4_PER_MAX/2, PWM4_PER_MAX);
	pid_set_param(ppid, 5.0f, 0.0f, 0.0f);

	lastTickCount = xTaskGetTickCount();
	lastTimestampCount = lastTickCount;

	usart_printf("\r\nMotors Task Create");

	while(1) {
		currentTickCount = xTaskGetTickCount();
		adxl345_read_x_axis(&xAxis);
		kxAxis = (int16_t)kalman_filter(pkfp, xAxis);
		pidOut = pid_calc(ppid, kxAxis);
		car_stand_control(pidOut);

		TickCount = currentTickCount - lastTickCount;
		if (TickCount > pdMS_TO_TICKS(500)) {
			lastTickCount = currentTickCount;

			usart_printf("\r\n[%d] raw:%d, kal:%d, pid:%d, PO:%d, IO:%d, DO:%d",
				currentTickCount / configTICK_RATE_HZ, xAxis, kxAxis, pidOut, ppid->pOut, ppid->iOut, ppid->dOut);
		}

		vTaskDelay(10);
	}
}


