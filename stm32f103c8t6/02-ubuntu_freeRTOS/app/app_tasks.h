#ifndef __APP_TASKS__
#define __APP_TASKS__

#include "FreeRTOS.h"
#include "task.h"
 
void task_main(void* pvParamenters);
void subtask1_sensors(void *pvParameters);
void subtask2_motors(void *pvParameters);
extern void create_subtasks(void);

#endif	/* end __APP_TASKS__ */
