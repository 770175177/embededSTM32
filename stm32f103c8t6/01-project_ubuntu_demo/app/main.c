#include "stm32f10x.h"
#include "delay.h"
#include "usart1.h"
#include "led.h"

int main(void)
{  
  delay_init();
  led_init();       // PC13

  while (1)
  {
    led_switch(LED_OFF);
    delay_ms(500);
    led_switch(LED_ON);
    delay_ms(500);
  }
}


