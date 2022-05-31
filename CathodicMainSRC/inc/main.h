/*************************************************************
//	Main program
//	------------------------------------------------------
//	Project Name : Cathodic Debonding Tester
//	Model Name  : ACT-100M
//	Start Date  : 2016.06.17
//	Chip Number : STM32F103VGT
//	C-Compiler	: EWARM
//	Written by 	: jhKim
//  COPYRIGHT (c) 2010 AddSol All rights reserved.
**************************************************************/
 
#ifndef __MAIN_H__
#define __MAIN_H__

#define ADCBUFFER		400

extern volatile unsigned short ADCValues[ADCBUFFER];

void System_Init(void);
void Variable_Initial( void );
void GPIO_Config(void);

void ALive_Cpu(void);
void Key_Process_Task(void);
void Key_Press_Check_Task(void);

void INT_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void PWM_Configuration(u32 Hz); 

void DMA_Config(void);
void ADC_Config(void);
void EXTI_Configuration(void);
void TIMER_INT2_Configuration(void);
void Led_Process_Task(void);



 
/////////////////////////////////////////////////////////
void Lcd_Nibble_Cmd_Set(u8 Data);
void Lcd_Cmd_Set(u8 Data);
void Lcd_Dis_Addr(u8  addr);		/* lcd display address ouput */
void Lcd_Dis_Data(u8 Data);
void Lcd_Clear(void);
void Lcd_Initial(void);
void Lcd_String_Write(u8 addr,u8 *str);
void Lcd_Length_Write(u8 addr,u8 *str, u8 length);
void Lcd_Char_Write(u8 addr,u8 c);
void Lcd_DataPort(u8 Data);
void Lcd_DataPort_Output(u8 Data);

void LCD_print(void);
void Clock_count(void);
void Clock_Setting(void);
void Clock_Count_Check(void);
void Lcd_Setting_Print_Set(void);

#endif   // __MAIN_H__
