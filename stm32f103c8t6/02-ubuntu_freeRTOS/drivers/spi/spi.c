#include "adxl345.h"

static SPI_InitTypeDef  SPI_InitStructure = {0};

void spi1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);	
 
	GPIO_InitStructure.GPIO_Pin = SPI1_NSS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK_PIN | SPI1_MISO_PIN | SPI1_MOST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// SPI directory is RX & TX
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						// master SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					// send data frame is 8 bits
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;							// CPOL is high
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;						// CPHA is second edge to capture
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							// NSS controled by software/hardware
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; // boardrate is devided to 32
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					// data transfer start at MSB
	SPI_InitStructure.SPI_CRCPolynomial = 7;							// CRC calculate

	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);												// enable SPI
}

void adxl345_spi1_set_speed(u8 speed)
{
	SPI_InitStructure.SPI_BaudRatePrescaler = speed ;
  	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
}

int8_t spi1_write_read_byte(u8 tx_data, u8 *rx_data)
{		
	u8 retry = 0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) { 	// send buffer empty
		retry++;
		if(retry > 200)
			return -1;
	}			  
	SPI_I2S_SendData(SPI1, tx_data); 									// send a data
	
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {	// recv buffer is not empty
		retry++;
		if(retry > 200)
			return -2;
	}	    
	*rx_data = SPI_I2S_ReceiveData(SPI1);

	return 0;
}































