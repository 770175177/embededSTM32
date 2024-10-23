#include <string.h>
#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
 
TaskHandle_t app_task1_handle = NULL;
TaskHandle_t app_task2_handle = NULL;
StackType_t  app_task1_stack[configMINIMAL_STACK_SIZE];
 
void App_Task1(void* pvParamenters);
void App_Task2(void* pvParamenters);
 
int main(void)
{
	//将全部优先级设为抢占优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  led_init();
  led_switch(LED_ON);
	
  //创建任务
	xTaskCreate((TaskFunction_t)App_Task1,          //任务入口函数
	            (const char *)"App_Task1",          //任务名字
							(uint16_t)configMINIMAL_STACK_SIZE, //任务栈大小
							(void*)NULL,                        //任务入口函数参数
							(UBaseType_t)1,                     //任务优先级
							(TaskHandle_t*)&app_task1_handle);  //任务句柄
	// //创建任务
	// xTaskCreate((TaskFunction_t)App_Task2,          //任务入口函数
	//             (const char *)"App_Task2",          //任务名字
	// 						(uint16_t)configMINIMAL_STACK_SIZE, //任务栈大小
	// 						(void*)NULL,                        //任务入口函数参数
	// 						(UBaseType_t)1,                     //任务优先级
	// 						(TaskHandle_t*)&app_task2_handle);  //任务句柄
								
	//开启任务调度器						
	vTaskStartScheduler();
}
 
void App_Task1(void *pvParameters)
{
  u8 led = LED_OFF;
  led_switch(led);
	

  for(;;)
	{
    led_switch(led);
    vTaskDelay(500);
    led = !led;
    led_switch(led);
    vTaskDelay(500);
	}
}
 
void App_Task2(void *pvParameters)
{
 

  uart_init(115200);
  for(;;)
	{
		
	}
}

// void hardware_init()
// {
//     delay_init();
//     led_init();       // PC13
//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//     uart_init(115200);
// }
