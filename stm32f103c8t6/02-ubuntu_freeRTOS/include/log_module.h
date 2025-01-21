#ifndef __LOG_MODULE__
#define __LOG_MODULE__
#include "usart.h"

enum _LOG_MODULE {
    PRINT_MODULE_TASK_MAIN  = 0x1,
    PRINT_MODULE_TASK_MOTOR = 0x2,
    PRINT_MODULE_ADXL345    = 0x4,
    PRINT_MODULE_MAX
};

#define PRINT_MODULE_ALL    0xFFFFFFFF

extern uint32_t print_flag;


#define PRINT_MODULE(mod,fmt,...)                                   \
            do {					                                \
				if (print_flag & mod)			                    \
					usart_printf("%s[%d]:"fmt,				        \
								__func__, __LINE__, __VA_ARGS__);	\
			} while (0)

#define TASK_MAIN_PRINT(fmt,...)    PRINT_MODULE(PRINT_MODULE_TASK_MAIN,fmt,__VA_ARGS__)

#define TASK_MOTOR_PRINT(fmt,...)   PRINT_MODULE(PRINT_MODULE_TASK_MOTOR,fmt,__VA_ARGS__)

#define ADXL345_PRINT(fmt,...)      PRINT_MODULE(PRINT_MODULE_ADXL345,fmt,__VA_ARGS__)

#endif  /* __LOG_MODULE__ */