/*************************************************************
//	uart program
//	------------------------------------------------------
//	Project Name : Cathodic Debonding Tester
//	Model Name  : ACT-100M
//	Start Date  : 2016.06.17
//	Chip Number : STM32F103VGT
//	C-Compiler	: EWARM
//	Written by 	: jhKim
//  COPYRIGHT (c) 2010 AddSol All rights reserved.
**************************************************************/

#ifndef __UART_H__
#define __UART_H__

#define ESC		0x1b



#define MCLK (72000000)
#define BAUD (115200)

#define BAUD9600 	(9600)
#define BAUD19200 	(19200)
#define BAUD57600 	(57600)
#define BAUD115200 	(115200)

void USART_Configuration(void);
void Send_Usart1(u8 buffer[], u8 size);
void Send_Usart2(u8 buffer[], u8 size);
void Send_Usart3(u8 buffer[], u8 size);
void Send_Usart4(u8 buffer[], u8 size);
void Send_Debug(char  *s, u8 type);

#endif /*__UART_H__*/

