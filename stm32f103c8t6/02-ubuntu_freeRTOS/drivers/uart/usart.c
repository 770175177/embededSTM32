#include "sys.h"
#include "misc.h"
#include "usart.h"
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"
#endif

static u8 USART_RX_BUF[USART_REC_LEN];
ring_buffer_t usart_rb;

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

int usart_gets(char* s)
{
	char data;
	int i = 0;

	while(ring_buffer_peek(&usart_rb, &data, i++)) {
		if((data == '\r') || (data == '\n')) {
			ring_buffer_dequeue_arr(&usart_rb, s, i);
			s[i-1] = '\0';

			return i - 1;
		}
	}

	return 0;
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

  
void uart_init(u32 bound)
{
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

	ring_buffer_init(&usart_rb, USART_RX_BUF, sizeof(USART_RX_BUF));
}

void USART1_IRQHandler(void)
{
	u8 res;
#if SYSTEM_SUPPORT_OS
	OSIntEnter();
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		res = USART_ReceiveData(USART1);

		ring_buffer_queue(&usart_rb, res);
     } 
#if SYSTEM_SUPPORT_OS
	OSIntExit();										 
#endif
}
	
