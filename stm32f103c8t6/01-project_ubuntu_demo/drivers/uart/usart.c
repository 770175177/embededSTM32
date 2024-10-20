#include "sys.h"
#include "misc.h"
#include "usart.h"
#include <stdarg.h>
#if SYSTEM_SUPPORT_OS
#include "includes.h"
#endif

#if 0
#pragma import(__use_no_semihosting)                           
struct __FILE  { 
	int handle; 
};
struct stat {
	off_t st_size;
};
typedef char *caddr_t;
typedef long int off_t;
typedef int pid_t;

FILE __stdout;       
void _sys_exit(int x) { x = x; }
int _write_r (struct _reent *ptr, int fd, const char *buf, size_t nbyte) { ; }
caddr_t _sbrk_r (struct _reent *ptr, ptrdiff_t incr) { ; }
int _close_r (struct _reent *ptr, int fd) { ; }
void abort (void) { while(1); }
int _read_r (struct _reent *ptr, int fd, char *buf, size_t nbyte) { ; }
off_t _lseek_r (struct _reent *ptr, int fd, off_t pos, int whence) { ; }
int _fstat_r (struct _reent *ptr, int fd, struct stat *buf) { ; }
int _isatty_r (struct _reent *ptr, int fd) { ; }
int _kill_r (struct _reent *ptr, pid_t pid, int sig) { ; }
pid_t _getpid_r (struct _reent *ptr, pid_t *pid) { ; }

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);  
    USART1->DR = (u8) ch;      
	return ch;
}
#else

int usart_puts(char* s)
{
	char *p = s;

	while(*p != '\0') {
		while((USART1->SR & 0X40)==0);
    	USART1->DR = (unsigned char)*p;
		p++;
	}

	return (p-s);
}

int usart_printf(const char *fmt, ...)
{
	int ret;
	char mini_buff[USART_PRINT_LEN];
	va_list va;

	va_start(va, fmt);
	ret = mini_vsnprintf(mini_buff, USART_PRINT_LEN, fmt, va);
	va_end(va);
	ret = usart_puts(mini_buff);

	return ret;
}

#endif

#if EN_USART1_RX
u8 USART_RX_BUF[USART_REC_LEN];
// bit15 complete flag, bit14 receive 0xd, bit13-0 received num
u16 USART_RX_STA=0;
  
void uart_init(u32 bound) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
  
	// USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// USART1_RX	  GPIOA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Usart1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
	u8 res;
#if SYSTEM_SUPPORT_OS
	OSIntEnter();
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		res =USART_ReceiveData(USART1);

		if((USART_RX_STA & 0x8000)==0) {
			if(USART_RX_STA & 0x4000) {
				if(res != 0x0a)				// \r
					;// USART_RX_STA = 0;
				else
					USART_RX_STA |= 0x8000;
			} else {
				if(res == 0x0d)				// \n
					USART_RX_STA|=0x4000;
				else {
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = res;
					USART_RX_STA++;
					if(USART_RX_STA > (USART_REC_LEN - 1))
						USART_RX_STA=0;
				}		 
			}
		} 
     } 
#if SYSTEM_SUPPORT_OS
	OSIntExit();										 
#endif
}
#endif	
