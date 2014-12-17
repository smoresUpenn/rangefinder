/*********************************************
// MAEVARM M4 STM32F373 SCCB
// date: March, 2013
// author: Chao Liu (chao.liu0307@gmail.com)
**********************************************/

#ifndef _SCCB_H
#define _SCCB_H

#include "mGeneral.h"

#define SCCB_SIO_C		8	   //SCL	PE8
#define SCCB_SIO_D		9	   //SDA	PE9

#define SIO_C_SET		{GPIOE->BSRR =(1<<SCCB_SIO_C);}
#define SIO_C_CLR		{GPIOE->BRR = (1<<SCCB_SIO_C);}
#define SIO_D_SET		{GPIOE->BSRR =(1<<SCCB_SIO_D);}
#define SIO_D_CLR		{GPIOE->BRR = (1<<SCCB_SIO_D);}

#define SIO_D_IN	    {GPIO_InitStructure.GPIO_Pin = 1<<SCCB_SIO_D;\
                         GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                         GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;\
                         GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
						 GPIO_Init(GPIOE, &GPIO_InitStructure); }

#define SIO_D_OUT	 {GPIO_InitStructure.GPIO_Pin = 1<<SCCB_SIO_D;\
	     	          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;\
					  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;\
					  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
                      GPIO_Init(GPIOE, &GPIO_InitStructure);}

#define SIO_D_STATE	((GPIOE->IDR&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))


/********* public functions ************/
void DelaySCCB(void);
void InitSCCB(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
u8 SCCBwriteByte(u8 m_data);
u8 SCCBreadByte(void);


#endif /* _SCCB_H */
