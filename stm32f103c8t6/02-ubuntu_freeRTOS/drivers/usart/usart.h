#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "mini_printf.h"
#include "ring_buffer.h"

#define USART_REC_LEN  			256
#define USART_PRINT_LEN  	    128
	  	
// extern u8  USART_RX_BUF[USART_REC_LEN];
// extern u8 USART_RX_STA;
extern ring_buffer_t usart_rb;

void uart_init(u32 bound);
void usart1_init(u32 bound);
int usart_printf(const char *fmt, ...);
int usart_puts(char* s);
int usart_gets(char* s);
int usart_getc(char *c);
int usart_putc(char c);

#endif


