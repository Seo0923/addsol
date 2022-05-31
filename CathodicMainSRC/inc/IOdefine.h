/*************************************************************
//	iodefine program
//	------------------------------------------------------
//	Project Name : Cathodic Debonding Tester
//	Model Name  : ACT-100M
//	Start Date  : 2016.06.17
//	Chip Number : STM32F103VGT
//	C-Compiler	: EWARM
//	Written by 	: jhKim
//  COPYRIGHT (c) 2010 AddSol All rights reserved.
**************************************************************/


#ifndef __IODEFINE_H__
#define __IODEFINE_H__

///////////////////////////////////////////////////////////////////////////////////

#define UART_WIFI			UART4
#define UART_INVERTER2		USART3
#define UART_INVERTER1		USART2
#define UART_LCD			USART1

///////////////////////////////////////////////////////////////////////////////////

#define 	LCD_RW_L				GPIO_ResetBits(GPIOC, GPIO_Pin_6)

#define 	LCD_D4_L		GPIO_ResetBits(GPIOC, GPIO_Pin_0)
#define 	LCD_D5_L		GPIO_ResetBits(GPIOC, GPIO_Pin_1)
#define 	LCD_D6_L		GPIO_ResetBits(GPIOC, GPIO_Pin_2)
#define 	LCD_D7_L		GPIO_ResetBits(GPIOC, GPIO_Pin_3)

#define 	LCD_D4_H		GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define 	LCD_D5_H		GPIO_SetBits(GPIOC, GPIO_Pin_1)
#define 	LCD_D6_H		GPIO_SetBits(GPIOC, GPIO_Pin_2)
#define 	LCD_D7_H		GPIO_SetBits(GPIOC, GPIO_Pin_3)

#define 	LCD_E_L			GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define 	LCD_RS_L		GPIO_ResetBits(GPIOC, GPIO_Pin_5)

#define 	LCD_E_H		GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define 	LCD_RS_H		GPIO_SetBits(GPIOC, GPIO_Pin_5)


#define 	CH4_ERRLED_ON			GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#define 	CH4_GOODLED_ON		GPIO_ResetBits(GPIOD, GPIO_Pin_7)
#define 	CH3_ERRLED_ON			GPIO_ResetBits(GPIOD, GPIO_Pin_6)
#define 	CH3_GOODLED_ON		GPIO_ResetBits(GPIOD, GPIO_Pin_5)
#define 	CH2_ERRLED_ON			GPIO_ResetBits(GPIOD, GPIO_Pin_4)
#define 	CH2_GOODLED_ON		GPIO_ResetBits(GPIOD, GPIO_Pin_3)
#define 	CH1_ERRLED_ON			GPIO_ResetBits(GPIOD, GPIO_Pin_2)
#define 	CH1_GOODLED_ON		GPIO_ResetBits(GPIOD, GPIO_Pin_1)
#define 	CHECKLED_ON			GPIO_ResetBits(GPIOD, GPIO_Pin_0)

#define 	CH4_ERRLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_8)
#define 	CH4_GOODLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_7)
#define 	CH3_ERRLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_6)
#define 	CH3_GOODLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define 	CH2_ERRLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define 	CH2_GOODLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_3)
#define 	CH1_ERRLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define 	CH1_GOODLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_1)
#define 	CHECKLED_OFF			GPIO_SetBits(GPIOD, GPIO_Pin_0)

#define 	CH4_ERRLED_TOGGLE		GPIOD->ODR^=GPIO_Pin_8
#define 	CH4_GOODLED_TOGGLE	GPIOD->ODR^=GPIO_Pin_7
#define 	CH3_ERRLED_TOGGLE		GPIOD->ODR^=GPIO_Pin_6
#define 	CH3_GOODLED_TOGGLE	GPIOD->ODR^=GPIO_Pin_5
#define 	CH2_ERRLED_TOGGLE		GPIOD->ODR^=GPIO_Pin_4
#define 	CH2_GOODLED_TOGGLE	GPIOD->ODR^=GPIO_Pin_3
#define 	CH1_ERRLED_TOGGLE		GPIOD->ODR^=GPIO_Pin_2
#define 	CH1_GOODLED_TOGGLE	GPIOD->ODR^=GPIO_Pin_1
#define 	CHECKLED_TOGGLE		GPIOD->ODR^=GPIO_Pin_0

#define 	ERRLED_ON			GPIO_ResetBits(GPIOD, GPIO_Pin_2)
#define 	GOODLED_ON		GPIO_ResetBits(GPIOD, GPIO_Pin_1)

#define 	ERRLED_OFF			GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define 	GOODLED_OFF		GPIO_SetBits(GPIOD, GPIO_Pin_1)

#define 	ERRLED_TOGGLE		GPIOD->ODR^=GPIO_Pin_2
#define 	GOODLED_TOGGLE	GPIOD->ODR^=GPIO_Pin_1



#define 	CH1_B_PLUS_ON			GPIO_SetBits(GPIOB, GPIO_Pin_0)	//HIGH
#define 	CH1_OPENCTL_ON		GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define 	CH1_CLOSECTL_ON		GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define 	CH2_B_PLUS_ON			GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define 	CH2_OPENCTL_ON		GPIO_SetBits(GPIOB, GPIO_Pin_10)
#define 	CH2_CLOSECTL_ON		GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define 	CH3_B_PLUS_ON			GPIO_SetBits(GPIOE, GPIO_Pin_0)
#define 	CH3_OPENCTL_ON		GPIO_SetBits(GPIOE, GPIO_Pin_1)
#define 	CH3_CLOSECTL_ON		GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define 	CH4_B_PLUS_ON			GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define 	CH4_OPENCTL_ON		GPIO_SetBits(GPIOE, GPIO_Pin_8)
#define 	CH4_CLOSECTL_ON		GPIO_SetBits(GPIOE, GPIO_Pin_9)

#define 	CH1_B_PLUS_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_0) //LOW
#define 	CH1_OPENCTL_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define 	CH1_CLOSECTL_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_2)
#define 	CH2_B_PLUS_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define 	CH2_OPENCTL_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_10)
#define 	CH2_CLOSECTL_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_11)
#define 	CH3_B_PLUS_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_0)
#define 	CH3_OPENCTL_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_1)
#define 	CH3_CLOSECTL_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define 	CH4_B_PLUS_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_7)
#define 	CH4_OPENCTL_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_8)
#define 	CH4_CLOSECTL_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_9)


#define 	READ_CH1_MTPWRA		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)
#define 	READ_CH1_MTPWRB		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)
#define 	READ_CH1_SENSORA		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)
#define 	READ_CH1_SENSORB		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)

#define 	READ_CH2_MTPWRA		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)
#define 	READ_CH2_MTPWRB		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)
#define 	READ_CH2_SENSORA		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
#define 	READ_CH2_SENSORB		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)

#define 	READ_CH3_MTPWRA		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define 	READ_CH3_MTPWRB		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define 	READ_CH3_SENSORA		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)
#define 	READ_CH3_SENSORB		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)

#define 	READ_CH4_MTPWRA		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)
#define 	READ_CH4_MTPWRB		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)
#define 	READ_CH4_SENSORA		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define 	READ_CH4_SENSORB		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)

#define 	READ_START				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define 	READ_STOP				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define 	READ_SW3				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)

#define 	LED1_ON				GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define 	LED2_ON				GPIO_ResetBits(GPIOA, GPIO_Pin_2)

#define 	LED1_OFF				GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define 	LED2_OFF				GPIO_SetBits(GPIOA, GPIO_Pin_2)

#define 	BUZZER_ON				GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define 	BUZZER_OFF				GPIO_ResetBits(GPIOA, GPIO_Pin_0)


///////////////////////////////////////////////////////////////////////////////////

#endif /*__IODEFINE_H__*/

