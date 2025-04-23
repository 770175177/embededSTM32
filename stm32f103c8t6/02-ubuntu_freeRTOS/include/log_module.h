#ifndef __LOG_MODULE__
#define __LOG_MODULE__
#include "usart.h"

enum _LOG_MODULE {
    PRINT_MODULE_TASK_MAIN  = 0x1,
    PRINT_MODULE_TASK_MOTOR = 0x2,
    PRINT_MODULE_ADXL345    = 0x4,
    PRINT_MODULE_OLED    = 0x8,
    PRINT_MODULE_MAX
};

#define PRINT_MODULE_ALL    0xFFFFFFFF

extern uint32_t error_flag;
extern uint32_t warn_flag;
extern uint32_t print_flag;
extern uint32_t debug_flag;

#define ERROR_MODULE(mod,fmt,...)                                   \
            do {					                                \
				if (error_flag & mod)			                    \
					usart_printf("%s[%d]:"fmt,				        \
								__func__, __LINE__, __VA_ARGS__);	\
			} while (0)

#define WARN_MODULE(mod,fmt,...)                                    \
            do {					                                \
				if (warn_flag & mod)			                    \
					usart_printf("%s[%d]:"fmt,				        \
								__func__, __LINE__, __VA_ARGS__);	\
			} while (0)

#define PRINT_MODULE(mod,fmt,...)                                   \
            do {					                                \
				if (print_flag & mod)			                    \
					usart_printf("%s[%d]:"fmt,				        \
								__func__, __LINE__, __VA_ARGS__);	\
			} while (0)

#define DEBUG_MODULE(mod,fmt,...)                                   \
            do {					                                \
				if (debug_flag & mod)			                    \
					usart_printf("%s[%d]:"fmt,				        \
								__func__, __LINE__, __VA_ARGS__);	\
			} while (0)

#define TASK_MAIN_PRINT(fmt,...)    PRINT_MODULE(PRINT_MODULE_TASK_MAIN,fmt,__VA_ARGS__)

#define TASK_MOTOR_PRINT(fmt,...)   PRINT_MODULE(PRINT_MODULE_TASK_MOTOR,fmt,__VA_ARGS__)

#define ADXL345_ERROR(fmt,...)      ERROR_MODULE(PRINT_MODULE_ADXL345,fmt,__VA_ARGS__)
#define ADXL345_PRINT(fmt,...)      PRINT_MODULE(PRINT_MODULE_ADXL345,fmt,__VA_ARGS__)
#define ADXL345_DEBUG(fmt,...)      DEBUG_MODULE(PRINT_MODULE_ADXL345,fmt,__VA_ARGS__)

#define OLED_ERROR(fmt,...)         ERROR_MODULE(PRINT_MODULE_OLED,fmt,__VA_ARGS__)
#define OLED_PRINT(fmt,...)         PRINT_MODULE(PRINT_MODULE_OLED,fmt,__VA_ARGS__)
#define OLED_DEBUG(fmt,...)         DEBUG_MODULE(PRINT_MODULE_OLED,fmt,__VA_ARGS__)

#endif  /* __LOG_MODULE__ */