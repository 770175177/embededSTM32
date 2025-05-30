#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

//-----------------����OLED�˿ڶ���----------------

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET)//CLK
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4, GPIO_PIN_RESET)//RES
#define OLED_RST_Set() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4, GPIO_PIN_SET)


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);

#endif









