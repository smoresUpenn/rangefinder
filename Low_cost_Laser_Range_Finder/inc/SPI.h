//-----------------------------------------------------------------------------
// MAEVARM M4 STM32F373 USART
// date: May 12, 2013
// author: Chao Liu (chao.liu0307@gmail.com)
//-----------------------------------------------------------------------------

#ifndef __SPI_H
#define __SPI_H

#include "mGeneral.h"

#define SPIenable   SPI_Cmd(SPI3, ENABLE)
#define SPIdisable  SPI_Cmd(SPI3, DISABLE)

void SPI3_Init(void);

u16 SPIx_ReadWriteByte(u16 TxData);

#endif 
