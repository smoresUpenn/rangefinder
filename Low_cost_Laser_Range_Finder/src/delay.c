/*********************************************
// MAEVARM M4 STM32F373 Delay
// date: March, 2013
// author: Chao Liu (chao.liu0307@gmail.com)
**********************************************/
#include "mGeneral.h"
#include "delay.h"
 u8   fac_us;      
 u16  fac_ms;

//initialize the accurate delay function
void delay_init(u8 SYSCLK)  // the system clock is 72MHz, SYSCLK = 72
{
 SysTick->CTRL&=0xfffffffb;  //use internal clock, HCLK/8
// SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
 fac_us=SYSCLK/8;      
 fac_ms=(u16)fac_us*1000;
} 

//********** millisecond delay function *************//
void delay_ms(u16 time_ms)
{         
 u32 temp;     
 SysTick->LOAD=(u32)time_ms*fac_ms;  // load the duration
 //SysTick_SetReload((u32)nms*fac_ms);
 SysTick->VAL =0x00;    // clear the counter
 //SysTick_CounterCmd(SysTick_Counter_Clear);
 SysTick->CTRL=0x01 ;          //¿ªÊ¼µ¹Êý 
 //SysTick_CounterCmd(SysTick_Counter_Enable); 
 do
 {
  temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));    // wait until the end of the duration   
 SysTick->CTRL=0x00;       // shut down the counter
 SysTick->VAL =0x00;       // clear the counter
}   

//********** microsecond delay function *************//
void delay_us(u32 time_us)
{  
 u32 temp;       
 SysTick->LOAD=time_us*fac_us; //load the duration      
 SysTick->VAL=0x00;        //clear the counter
 SysTick->CTRL=0x01 ;      //begin to count
 do
 {
  temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));    // wait until the end of the duration   
 SysTick->CTRL=0x00;       // shut down the counter
 SysTick->VAL =0X00;       // clear the counter
}  
