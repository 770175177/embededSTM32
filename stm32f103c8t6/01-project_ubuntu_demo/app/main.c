#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"

void hardware_init();

int main(void)
{ 
    u8 len, led = LED_OFF;
    u16 times = 0;
    int n;

    hardware_init();
    usart_printf("hello my mini printf\r\n");

    while (1) {
      if(USART_RX_STA & 0x4000) {			   
        len = USART_RX_STA & 0x3fff;
        usart_printf("\nsend message is: %s\n", USART_RX_BUF);
        USART_RX_STA=0;
      } else {
        times++;
        if(times % 400 == 0) {
          usart_printf("printf index %d\r\n", times);
        }
        if(times % 100 == 0) {
          led = !led;
          led_switch(led);
        }
        delay_ms(10);
      }
    }
}

void hardware_init()
{
    delay_init();
    led_init();       // PC13
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);
}
