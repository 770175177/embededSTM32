#include "app_tasks.h"
#include "app_init.h"
 
int main(void)
{
	BaseType_t ret = pdPASS;
	TaskHandle_t main_task_handle = NULL;

	// 初始化硬件等
	app_init();

	// 创建任务
	ret = xTaskCreate((TaskFunction_t)main_task,        // 任务入口函数
	            	(const char *)"Main Task",          // 任务名字
					(uint16_t)configMINIMAL_STACK_SIZE, // 任务栈大小
					(void*)NULL,                        // 任务入口函数参数
					(UBaseType_t)1,                     // 任务优先级
					(TaskHandle_t*)&main_task_handle);  // 任务句柄
	configASSERT(ret == pdPASS);
								
	// 开启任务调度器						
	vTaskStartScheduler();
}
