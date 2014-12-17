/*********************************************
// MAEVARM M4 STM32F373 SCCB
// date: March, 2013
// author: Chao Liu (chao.liu0307@gmail.com)
**********************************************/

#include "SCCB.h"

GPIO_InitTypeDef GPIO_InitStructure;
/***********************************************
    delay function
************************************************/
void DelaySCCB(void) 
{
	volatile int i;
	for(i=0;i<1500;i++);
}

/***************************************************************************
    initialize the SCCB, PE8--SCL, PE9--SDA, change them in the header file
****************************************************************************/
void InitSCCB(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    
   	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
   	GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);
	RCC_MCOConfig(RCC_MCOSource_HSE);

}
/*****************************************************
    SCCB start signal
****************************************************/
void startSCCB(void)
{
    SIO_D_SET;     // high in SDA
    DelaySCCB();

    SIO_C_SET;	   // high in SCL
    DelaySCCB();

    SIO_D_CLR;     // low in SDA
    DelaySCCB();

    SIO_C_CLR;	   // low in SCL
    DelaySCCB();

}
/*************************************
    SCCB stop signal
**************************************/
void stopSCCB(void)
{
    SIO_D_CLR;
    DelaySCCB();

    SIO_C_SET;
    DelaySCCB();

    SIO_D_SET;
    DelaySCCB();
}

/********************************************************************
    if reading data consecutively, noAck is used in the last period
*********************************************************************/
void noAck(void)
{
	DelaySCCB();
	SIO_D_SET;
	DelaySCCB();
	
	SIO_C_SET;
	DelaySCCB();
	
	SIO_C_CLR;
	DelaySCCB();
	
	SIO_D_CLR;
	DelaySCCB();
}

/****************************************
    write 1 byte to SCCB
*****************************************/
u8 SCCBwriteByte(u8 m_data)
{
	unsigned char j,tem;
	for(j=0;j<8;j++) 
	{
		if((m_data<<j)&0x80)
		{
			SIO_D_SET;
		}
		else
		{
			SIO_D_CLR;
		}
		DelaySCCB();
		SIO_C_SET;
		DelaySCCB();
		SIO_C_CLR;
		DelaySCCB();
	}
	DelaySCCB();
	
	SIO_D_IN; // set SDA input
	DelaySCCB();
	SIO_C_SET;
	DelaySCCB();
	DelaySCCB();
	DelaySCCB();
	
	if(SIO_D_STATE)
	{
		tem=0;   // SDA=1, failed, return 0
	}
	else
	{
		tem=1;   // SDA=0, successful, return 1
	}
	SIO_C_CLR;
	DelaySCCB();
	
	SIO_D_OUT;   // set SDA output
	return(tem);  
}

/************************************************
    read 1 byte from SCCB
*************************************************/
u8 SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SIO_D_IN;  // set SDA input
	
	for(j=8;j>0;j--) 
	{		     
		DelaySCCB();
		SIO_C_SET;
		DelaySCCB();
		DelaySCCB();
		DelaySCCB();
		read=read<<1;
		if(SIO_D_STATE) 
		{
			read=read+1;
		}
		SIO_C_CLR;
	}
	SIO_D_OUT;    // set SCCB output
	return(read);
}
