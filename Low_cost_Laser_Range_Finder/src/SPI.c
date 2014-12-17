//-----------------------------------------------------------------------------
// MAEVARM M4 STM32F373 SPI
// date: May 12, 2013
// author: Chao Liu (chao.liu0307@gmail.com)
//-----------------------------------------------------------------------------

#include "SPI.h"

void SPI3_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
	// SPI Pin Definition
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_6);    
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_6); 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_6); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;   // PA1=SCK PA2=MISO PA3=MOSI	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;   // PA4 NSS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	SPI_Cmd(SPI3, DISABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	//SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI3, &SPI_InitStructure); 
	SPI_Cmd(SPI3, ENABLE);
	
}

u16 SPIx_ReadWriteByte(u16 TxData)
{	
	
    while((SPI3->SR&SPI_I2S_FLAG_TXE)==RESET);
    SPI3->DR = TxData;

    while((SPI3->SR&SPI_I2S_FLAG_RXNE)==RESET);
    return (SPI3->DR);
	
}



