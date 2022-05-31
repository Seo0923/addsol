/***************************************************************************
 **
 **
 **    Master include file
 **
 **    Used with ARM IAR C/C++ Compiler
 **
 **    (c) Copyright IAR Systems 2008
 **
 **    $Revision: 34964 $
 **
 ***************************************************************************/

#ifndef __INCLUDES_H
#define __INCLUDES_H

//#define SIMULATOR

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <intrinsics.h>
#include <assert.h>

#include "stm32f10x.h"
#define IS_BIT(A,B)      ((A>>B)&0x01)    

#define sbit(x,y) (x |= (0x1<<y))  	
#define cbit(x,y) (x &= ~(0x1<<y)) 	


#define PC_RX_BUF_COUNT	150//3
#define PC_TX_BUF_COUNT	150
#define PC_RX_OVER_TM		10		/* Receive Over Time */

#define IN_RX_BUF_COUNT	150//3
#define IN_TX_BUF_COUNT	150
#define IN_RX_OVER_TM		50

#define EX_RX_BUF_COUNT	150//3
#define EX_TX_BUF_COUNT	150
#define EX_RX_OVER_TM		50

#define MAX_LIN_DATA		8
#define KEY_CHATTER_MAX	                100

#define MAX_CH				5

#define   REGISTER_ARRAY_MAX 	30
#define 	REGISTER_ARRAY_DROP	5

#define HZ_4000			4000
#define HZ_5000			5000

#define FLASH_SETDATA_START_ADD	0x80a0000;				//starting from Sector9 - 128KB
#define MAX_FLASH_DATA				96
#define SETTINGS_WORDS 	2//sizeof(settings)/4
/////////////////////////////////////
//#define DEBUG_TX_BUF_MAX		50


#define RX1_BUF_MAX		50
#define TX1_BUF_MAX		50
#define TX1_DATA_MAX		50

#define RX2_BUF_MAX		50
#define TX2_BUF_MAX		50
#define TX2_DATA_MAX		50

#define RX3_BUF_MAX		50
#define TX3_BUF_MAX		50
#define TX3_DATA_MAX		50

#define RX4_BUF_MAX		50
#define TX4_BUF_MAX		100
#define TX4_DATA_MAX		100
 
typedef void (*PFUNC_Int)(int);
typedef void (*PFUNC)(void);
///////////////////////////////////////////////////////////////////////////////////

typedef __packed struct
{
	u8	gu8_Cmd;
	u8	gu8_Device_ID;	
	u8   gu8_If_Cmd;
	u8	gu8_Value;
}IF_TASK;

typedef __packed struct
{
	u8	gu8_Cmd;
	u8	gu8_Device_ID;	
	u8	gu8_Is_If;  		//if cmd
	u8	gu8_Inverter_Cmd;
	u16  gu16_Data1;
	u16  gu16_Data2;
	u16  gu16_Task_Delay;	// after task execute
	IF_TASK  G_If_Task;
}TASK_LIST;

///////////////////////////////////////////////////////////////////////////////////


#define ADDR_HW		3
#define ADDR_SW			10
#define ADDR_WATT		17
#define ADDR_HZ			17
#define ADDR_V			0x40+2
#define ADDR_A			0x40+9
//#define ADDR_DUTY		0x40+17

#define LENGTH_HW		3
#define LENGTH_SW		3
#define LENGTH_WATT	3
#define LENGTH_HZ		3
#define LENGTH_V		4
#define LENGTH_A		4
#define LENGTH_DUTY	3

#define ADDR_STATE_RUN 	 16
#define ADDR_STATE_SLEEP     0x40+16
#define ADDR_STATE_WAKEUP 36
#define ADDR_RESULT_CH1	 0x40+20+2
#define ADDR_RESULT_CH2	 0x40+20+7
#define ADDR_RESULT_CH3	 0x40+20+12
#define ADDR_RESULT_CH4	 0x40+20+17

#define LENGTH_RUN			 4
#define LENGTH_SLEEP		 4
#define LENGTH_WAKEUP		 4
#define LENGTH_RESULT_CH1	 2
#define LENGTH_RESULT_CH2	 2
#define LENGTH_RESULT_CH3	 2
#define LENGTH_RESULT_CH4	 2

typedef enum 
{
	MOTOR_RUN,
	MOTOR_SLEEPMODE,
	MOTOR_WAKE_UP,
	MOTOR_CHECK_STOP,
}CHECK_STEP;


typedef enum 
{
	RUN_READY,
	RUN_MOTOR_RUN,
	RUN_MOTOR_RUN_CHECK,
	RUN_SLEEPMODE,
	RUN_SLEEPMODE_CHECK,
	RUN_WAKEUP,
	RUN_WAKEUP_CHECK,
	RUN_RESULT,	
}RUN_STEP;

typedef enum 
{
	BUZZER_READY,
	BUZZER_ERROR_START,
	BUZZER_ERROR_ON,
	BUZZER_ERROR_OFF,
	BUZZER_ERROR_END,
	BUZZER_GOOD_START,
	BUZZER_GOOD_END,
	BUZZER_KEY_START,
	BUZZER_KEY_END,
}BUZZER_STEP;

///////////////////////////////////////////////////////////////////////////////////

 
#endif  // __INCLUDES_H
