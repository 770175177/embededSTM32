#ifndef __SEGGER_RTT_PRINTF_H__
#define __SEGGER_RTT_PRINTF_H__

//! 调试输出配置
#define RTT_DBG_ENABLE          (1)

#if RTT_DBG_ENABLE
    #include "SEGGER_RTT.h"
	/* 初始化调试模块 */
    #define DEBUG_INIT()    SEGGER_RTT_Init()
    /* RTT 终端号 */
    #define RTT_DBG_PORT        0
    #define LOG_PROTO(type,color,format,...)                        \
            SEGGER_RTT_printf(RTT_DBG_PORT,"%s%s"format"\r\n%s",    \
                            color,                                  \
                            type,                                   \
                            ##__VA_ARGS__,                          \
                            RTT_CTRL_RESET)
    /* 清屏*/
    #define log_clear()     SEGGER_RTT_WriteString(RTT_DBG_PORT, "  "RTT_CTRL_CLEAR)
    /* 无颜色日志输出 */
    #define log_debug(format,...)   LOG_PROTO("D:","",format,##__VA_ARGS__)
    /* 有颜色格式日志输出 */
    #define log_info(format,...)    LOG_PROTO("I:", RTT_CTRL_TEXT_BRIGHT_GREEN , format, ##__VA_ARGS__)
    #define log_warn(format,...)    LOG_PROTO("W:", RTT_CTRL_TEXT_BRIGHT_YELLOW, format, ##__VA_ARGS__)
    #define log_error(format,...)   LOG_PROTO("E:", RTT_CTRL_TEXT_BRIGHT_RED   , format, ##__VA_ARGS__)

#else
    #define DEBUG_INIT()
    #define log_clear()
    #define log_debug
    #define log_info
    #define log_warn
    #define log_error
#endif

#endif      /* end __SEGGER_RTT_PRINTF_H__ */
