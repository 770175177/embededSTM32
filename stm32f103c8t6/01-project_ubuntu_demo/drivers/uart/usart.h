#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "mini_printf.h"

#define USART_REC_LEN  			128
#define USART_PRINT_LEN  	    64
#define EN_USART1_RX 			1
	  	
extern u8  USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;
void uart_init(u32 bound);
int usart_puts(char* s);
int usart_printf(const char *fmt, ...);

#endif


