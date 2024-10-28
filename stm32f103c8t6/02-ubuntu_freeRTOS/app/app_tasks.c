#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "app_tasks.h"
#include "app_cmd.h"
 
void main_task(void *pvParameters)
{
	TickType_t currentTickCount, TickCount;
	TickType_t lastTickCount, lastTimestampCount;

	lastTickCount = xTaskGetTickCount();
	lastTimestampCount = lastTickCount;
	cmd_setup();

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
			usart_printf("\r\n[%d] My FreeRTOS is running", currentTickCount/configTICK_RATE_HZ);
		}
	}
}

// void loop() {
//     char c;
//     if (cli == NULL)
//         return;

//     // provide all chars to cli
//     while (c = usart_getc()) {
//         embeddedCliReceiveChar(cli, c);
//     }

//     embeddedCliProcess(cli);
// }

// int main(void)
// {
// 	BaseType_t ret = pdPASS;
// 	TaskHandle_t main_task_handle = NULL;

// 	// 初始化硬件等
// 	app_init();

// 	// 创建任务
// 	ret = xTaskCreate((TaskFunction_t)main_task,        // 任务入口函数
// 	            	(const char *)"Main Task",          // 任务名字
// 					(uint16_t)configMINIMAL_STACK_SIZE, // 任务栈大小
// 					(void*)NULL,                        // 任务入口函数参数
// 					(UBaseType_t)1,                     // 任务优先级
// 					(TaskHandle_t*)&main_task_handle);  // 任务句柄
// 	configASSERT(ret == pdPASS);
								
// 	// 开启任务调度器						
// 	vTaskStartScheduler();
// }
