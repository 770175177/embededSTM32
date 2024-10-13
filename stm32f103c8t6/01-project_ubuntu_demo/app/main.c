#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"

void Delay(__IO u32 nCount);

int main(void)
{  
  SystemInit();       // 72M 
  USART1_Config();    // USART1
  led_config();       // PC13

  while (1)
  {
    // UART1Test();
    led_switch(LED_OFF);
    Delay(0x200000);
    led_switch(LED_ON);
    Delay(0x200000);
  }
}

void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 


