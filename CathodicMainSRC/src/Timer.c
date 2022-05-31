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

#include "includes.h"

#include "main.h"
#include "user.h"
#include "IOdefine.h"
#include "Uart.h"
#include "timer.h"
#include "mmi.h" 
#include "dsp.h"

#include <string.h>

//unsigned char Time1msec;						//Time 1msec	
unsigned short TMcnt;							/* 1msec Time count */
unsigned char fTMout;							/* 1msec Time over flag */

///////////////////////////////////////
extern u16	gu16ALive_Cpu_Dly;
extern u16	gu16_Key_Press_Dly; 
u8			gu8_500us_Toggle;
 
/////////////////////////////////////////////////////////

extern	u16		gu16_Sleep_Tmr;
extern	u16		gu16_MTR_Action_Dly;

/////////////////////////////////////////////////////////

extern	u16		gu16_Run_Step_Dly;
extern  u16             gu16_Setting_Step_Dly;
extern	u16		gu16_Buzzer_Mode_Dly;
extern	u8		gu8_Buzzer_On_Tm;

/*-----------------------------------------------------------
//	Timer Control service ( 500us )
-----------------------------------------------------------*/
void Timer_Control_Service(void)
{

////////////////1 ms  timer /////////////////////////////////////////////
	if(gu8_500us_Toggle)
	{
		if (fTMout)										//If Timer delay flag set ?
		{
			TMcnt--;
			if (!TMcnt) fTMout = FALSE;
		}
		if(gu16ALive_Cpu_Dly)gu16ALive_Cpu_Dly--;	
		if(gu16_Key_Press_Dly)gu16_Key_Press_Dly--;
		gu8_500us_Toggle = 0;

		//if(gu16_Sleep_Tmr)gu16_Sleep_Tmr--;
		//if(gu16_MTR_Action_Dly)gu16_MTR_Action_Dly--;
		if(gu16_Run_Step_Dly)gu16_Run_Step_Dly--;
                if(gu16_Setting_Step_Dly)gu16_Setting_Step_Dly--;
		if(gu16_Buzzer_Mode_Dly)gu16_Buzzer_Mode_Dly--;
		
		if(gu8_Buzzer_On_Tm)
		{
			gu8_Buzzer_On_Tm--;
			BUZZER_ON;
		}
		else
		{
			BUZZER_OFF;
		}
		
	}
	else
	{
		gu8_500us_Toggle = 1;
	}

}


/*------------------------------------------------------------
//		Time Delay msec
--------------------------------------------------------------*/
void Time_Delay(int SetTime)
{
	TMcnt = SetTime;
	fTMout = TRUE;
	while(fTMout);
}

void Delay_ms(int SetTime)
{
	TMcnt = SetTime;
	fTMout = TRUE;
	while(fTMout);
}

void Delay_us(u32 nCount)
{
	u32 index = 0;

	/* default system clock is 72MHz */
	for(index = (36 * nCount); index != 0; index--)
	{
	
	}
}


