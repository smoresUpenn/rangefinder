/*********************************************
// MAEVARM M4 STM32F373 Delay
// date: March, 2013
// author: Chao Liu (chao.liu0307@gmail.com)
**********************************************/

#ifndef __DELAY_H
#define __DELAY_H

void delay_init(u8 SYSCLK);
void delay_ms(u16 time_ms);
void delay_us(u32 time_us);

#endif

