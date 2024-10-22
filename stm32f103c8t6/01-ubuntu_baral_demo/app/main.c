#include "stm32f10x.h"
#include "delay.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include <string.h>

void hardware_init();

int main(void)
{ 
    u8 len, led = LED_OFF;
    u16 times = 0;
    u8 data[64] = {0};

    hardware_init();
    usart_printf("hello my mini printf\r\n");

    while (1) {
      if(len = usart_gets(data)) {			   
        usart_printf("get data is: %s(len=%d)\n", data, len);
      } else {
        times++;
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
