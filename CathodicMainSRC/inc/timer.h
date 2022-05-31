/*************************************************************
//	timer program
//	------------------------------------------------------
//	Project Name : Cathodic Debonding Tester
//	Model Name  : ACT-100M
//	Start Date  : 2016.06.17
//	Chip Number : STM32F103VGT
//	C-Compiler	: EWARM
//	Written by 	: jhKim
//  COPYRIGHT (c) 2010 AddSol All rights reserved.
**************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

#define SWSEL		0x01
#define SWSTART		0x02

void Timer_Control_Service(void);
void Delay_ms(int SetTime);
void Delay_us(u32 nCount);
#endif /*__TIMER_H__*/
