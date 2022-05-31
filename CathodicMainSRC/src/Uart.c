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

#include "includes.h"

#include "main.h"
#include "user.h"
#include "IOdefine.h"
#include "Uart.h"
#include "timer.h"
#include "mmi.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

extern 	u8	gu8_Tx1_Buf[TX1_BUF_MAX];
extern	u8	gu8_Tx1_Buf_Index;
extern	u8	gu8_Tx1_Buf_Length;

extern 	u8	gu8_Tx2_Buf[TX2_BUF_MAX];
extern	u8	gu8_Tx2_Buf_Index;
extern	u8	gu8_Tx2_Buf_Length;

extern 	u8	gu8_Tx3_Buf[TX3_BUF_MAX];
extern	u8	gu8_Tx3_Buf_Index;
extern	u8	gu8_Tx3_Buf_Length;

extern 	u8	gu8_Tx4_Buf[TX4_BUF_MAX];
extern	u8	gu8_Tx4_Buf_Index;
extern	u8	gu8_Tx4_Buf_Length;

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configurate the USART 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	//LCD Configuration
//  	USART_InitStructure.USART_BaudRate = BAUD115200;
  	USART_InitStructure.USART_BaudRate = BAUD9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_Init(UART_LCD, &USART_InitStructure);
	USART_ITConfig(UART_LCD, USART_IT_RXNE, ENABLE); 
	USART_ITConfig(UART_LCD, USART_IT_TXE, DISABLE);
	USART_Cmd(UART_LCD, ENABLE); 

	//Inverter1 Configuration
  	USART_InitStructure.USART_BaudRate = BAUD57600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_Init(UART_INVERTER1, &USART_InitStructure);
	USART_ITConfig(UART_INVERTER1, USART_IT_RXNE, ENABLE); 
	USART_ITConfig(UART_INVERTER1, USART_IT_TXE, DISABLE);
	USART_Cmd(UART_INVERTER1, ENABLE); 

	//Inverter2 Configuration
  	USART_InitStructure.USART_BaudRate = BAUD57600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_Init(UART_INVERTER2, &USART_InitStructure);
	USART_ITConfig(UART_INVERTER2, USART_IT_RXNE, ENABLE); 
  	USART_ITConfig(UART_INVERTER2, USART_IT_TXE, DISABLE);
	USART_Cmd(UART_INVERTER2, ENABLE); 

	//Wifi Configuration
  	USART_InitStructure.USART_BaudRate = BAUD9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	USART_Init(UART_WIFI, &USART_InitStructure);
	USART_ITConfig(UART_WIFI, USART_IT_RXNE, ENABLE); 
	USART_ITConfig(UART_WIFI, USART_IT_TXE, DISABLE);
	USART_Cmd(UART_WIFI, ENABLE); 

}

/*******************************************************************************
* Function Name  : Send_Pc
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//	void Send_Debug(u8 buffer[], u8 size)
//	{
//	    	int i=0;
//	
//	    	gu8_Debug_Tx_Buf_Index = 0;
//	    	gu8_Debug_Tx_Buf_Length = size
//	
//	  	for (i=0; i < size; ++i)
//	    	{
//	        	gu8_Tx1_Buf[ i] = buffer[ i];
//	    	}                          
//	    	USART_ITConfig(UART_WIFI, USART_IT_TXE, ENABLE);
//	}

void Send_Usart1(u8 buffer[], u8 size)
{
    int i=0;

    gu8_Tx1_Buf_Index = 0;
    gu8_Tx1_Buf_Length = size;

    for (i=0; i < size; ++i)
    {
        gu8_Tx1_Buf[ i] = buffer[ i];
    }             

    USART_ITConfig(UART_LCD, USART_IT_TXE, ENABLE);
}


void Send_Usart2(u8 buffer[], u8 size)
{
    int i=0;

    gu8_Tx2_Buf_Index = 0;
    gu8_Tx2_Buf_Length = size;

    for (i=0; i < size; ++i)
    {
        gu8_Tx2_Buf[ i] = buffer[ i];
    }             

    USART_ITConfig(UART_INVERTER1, USART_IT_TXE, ENABLE);
    Delay_ms(5);
}

void Send_Usart3(u8 buffer[], u8 size)
{
    int i=0;

    gu8_Tx3_Buf_Index = 0;
    gu8_Tx3_Buf_Length = size;

    for (i=0; i < size; ++i)
    {
        gu8_Tx3_Buf[ i] = buffer[ i];
    }             

    USART_ITConfig(UART_INVERTER2, USART_IT_TXE, ENABLE);

    Delay_ms(5);
}
void Send_Usart4(u8 buffer[], u8 size)
{
    int i=0;

    gu8_Tx4_Buf_Index = 0;
    gu8_Tx4_Buf_Length = size;

    for (i=0; i < size; ++i)
    {
        gu8_Tx4_Buf[ i] = buffer[ i];
    }             

    USART_ITConfig(UART_WIFI, USART_IT_TXE, ENABLE);
}





