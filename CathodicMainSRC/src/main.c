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

#include <string.h>
#include <math.h>
#include "includes.h"
#include "main.h"
#include "user.h"
#include "IOdefine.h"
#include "Uart.h"
#include "timer.h"
//#include "OutPut.h"
#include "Temp_Control.h"
#include "mmi.h" 
#include "io_macros.h"
#include "dsp.h"
#include "rpm_data.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_tim.h"

 
/* Private typedef -----------------------------------------------------------*/
 
 
static __IO ErrorStatus HSEStartUpStatus = SUCCESS;
u16 		gu16ALive_Cpu_Dly; 
u16		gu16_Key_Press_Dly;

///////////////////////////////////////////////////////////////////////////////////

char		gu8_Str1[30];       	// 변환한 문자열을 저장할 배열
char		gu8_Str2[30];       	// 변환한 문자열을 저장할 배열
char         gu8_date_str[30];


u8		gu8_Start_Chat;
u8		gu8_fStart_Enable;
u8		gu8_fStart;

u8		gu8_Stop_Chat;
u8		gu8_fStop_Enable;
u8		gu8_fStop;


u8		gu8_Check_Led;
u16		gu16_Run_Step_Dly;
u16           gu16_Setting_Step_Dly;


BUZZER_STEP	 gu8_Buzzer_Mode_Step;
u16			 gu16_Buzzer_Mode_Dly;
u8			 gu8_Error_Counter;
u8			 gu8_Buzzer_On_Tm;


u8                      gu8_Clock_setting_mode;
u8       gu8_Clock_setting_toggle = 0;

u8                      gu8_year1;
u8                      gu8_year2;
u8                      gu8_year3;
u8                      gu8_year4;
u8                      gu8_month;
u8                      gu8_day;
u8                      gu8_date;
u8                      gu8_hour;
u8                      gu8_min;
u8                      gu8_sec;
u32                     gu16_clock_sec_timer;
u16                     gu16_year_counter;
u8                       gu8_dayset;




/***********************************************************************
 	Function Name  : main
 	Parameter      : void
 	Returned Value : void
 	Comments       : SunRoof_SleepMode_4CH_Controller_20220519
***********************************************************************/
void main(void)
{
	System_Init();
	Variable_Initial();
	Lcd_Initial();
        LCD_print();
        
	while(1)
	{
		ALive_Cpu();		
		Key_Press_Check_Task();
		Key_Process_Task();
                Clock_count();
		//Run_Mode();
		//Buzzer_Mode();
		//Sleepmode_Check();
	}
}





/*******************************************************************************
* Function Name  : System_Init
* Description    : Initializes the System application.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void System_Init(void)
{
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
	    	/* HCLK = SYSCLK */
	    	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
	  
	    	/* PCLK2 = HCLK */
	    	RCC_PCLK2Config(RCC_HCLK_Div1); 
	
	    	/* PCLK1 = HCLK/4 */
	    	RCC_PCLK1Config(RCC_HCLK_Div2);
	
	    	/* Enable Prefetch Buffer */
	    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	    	/* Flash 2 wait state */
	    	FLASH_SetLatency(FLASH_Latency_2);
	
	    	/* PLLCLK = 8MHz * 9 = 72 MHz */
	    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
	
	    	/* Enable PLL */ 
	    	RCC_PLLCmd(ENABLE);
			
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
	
	/* Enable GPIO clock */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  	/* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  	/* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
 
  	/* Enable UART clock */
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
//  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);  
  	

	/* Enable DMA1 clock */
 //	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  	/* Enable ADC1 and GPIOC clock */
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  	/* TIM3  clocks enable */
//  	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE);
	// TIM8
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  	  	/* TIM4  clocks enable */
//  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


	/* GPIO Configuration */
	GPIO_Config();

	/* USRT Configuration */
//	USART_Configuration();


	/* Interrupt Configuration */
	//INT_Configuration();
//	ADC1_DMA_Init();
  
	NVIC_Configuration();

	SysTick_Configuration();
	
}






/***********************************************************************
 	Function Name  : GPIO_Config
 	Parameter      : void
 	Returned Value : void
 	Comments       : GPIO_Config
***********************************************************************/
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	///////////////////////////////////////////////////////////////////////////////////

  	// PORTA INPUT
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	// PORTA OUTPUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	// PORTB INPUT
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	 // PORTB OUTPUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_9|GPIO_Pin_10 |GPIO_Pin_11;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	// PORTC OUTPUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

  	// PORTD OUTPUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	 // PORTE INPUT
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
  	 // PORTE OUTPUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_7|GPIO_Pin_8 |GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
  
} 






/*******************************************************************************
* Function Name  : Variable_Initial
* Description    : Motor_Led_STOP
* Input          : void
* Output         : void
* Return         : void
*******************************************************************************/
void Variable_Initial( void )
{
	//////////////////////////////////////////////////////////////////////////////////
        gu16_year_counter = 2022;
        gu16_clock_sec_timer = 0;
          
          
        gu8_year1 = gu16_year_counter/1000;
        gu8_year2 = gu16_year_counter/100%10;
        gu8_year3 = gu16_year_counter/10%10;
        gu8_year4 = gu16_year_counter%10;
        gu8_month = 1;
        gu8_day = 1;
        gu8_date = 0;
        gu8_hour = 0;
        gu8_min = 0;
        gu8_sec = 0;
        sprintf(gu8_date_str,"Mon");

}




/*******************************************************************************
* Function Name  : SysTick_Configuration
* Description    : Configure a SysTick Base time to 10 ms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Configuration(void)
{
  	/* Setup SysTick Timer for 10 msec interrupts  */
  	//if (SysTick_Config(SystemCoreClock / 100))
  	//{ 
    		/* Capture error */ 
   	// while (1);
 	// }

  	/* Setup SysTick Timer for 1000 usec interrupts: 1000  */
  	/* Setup SysTick Timer for 500 usec interrupts : 2000 */
//  	if (SysTick_Config(72000000 / 1000))
  	if (SysTick_Config(72000000 / 2000))
  	{ 
    		/* Capture error */ 
    		while (1);
  	}
  
 	/* Configure the SysTick handler priority */
  	NVIC_SetPriority(SysTick_IRQn, 0x0);
}







/*******************************************************************************
* Function Name  : INT_Configuration
* Description    : Interrupt setting location
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void INT_Configuration(void)
{ 
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  	TIM_OCInitTypeDef        TIM_OCInitStructure;

  	/* Set the Vector Table base address at 0x08000000 */
  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);

  	/* TIM2 used for timing, the timing period depends on wav file sample rate */
  	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;    		/* TIM2CLK = 24 MHz */
  	TIM_TimeBaseStructure.TIM_Period = 24000;			// 1.0msec
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  	/* Output Compare Inactive Mode configuration: Channel1 */
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = 0x0;
  	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  	/* Start TIM2 */
  	TIM_Cmd(TIM2, ENABLE);

  	/* Enable TIM2 update interrupt */
  	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

}





/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configure the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
	 
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
    	//Enable DMA1 channel IRQ Channel
  	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM2 Interrupt */
//	  	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	  	NVIC_Init(&NVIC_InitStructure);


}




/***********************************************************************
 	Function Name  : Lcd_Initial
 	Parameter      : void
 	Returned Value : void
 	Comments       : Lcd Initial
***********************************************************************/
void Lcd_Initial(void)			/* lcd initial */
{
	LCD_RW_L;
	Delay_ms(15);			/* 10msec delay */
	Lcd_Nibble_Cmd_Set(0x30);	/* data length 4 bit */
	Delay_ms(5);				/* 1msec delay */
	Lcd_Nibble_Cmd_Set(0x30);	/* data length 4 bit */
	Delay_ms(5);				/* 1msec delay */
	Lcd_Nibble_Cmd_Set(0x30);	/* data length 4 bit */
	Delay_ms(5);				/* 1msec delay */
	Lcd_Nibble_Cmd_Set(0x20);	/* data length 4 bit */
	Delay_ms(5);				/* 1msec delay */

	Lcd_Cmd_Set(0x28);		/* data length 4 bit */
	Delay_ms(5);				/* 1msec delay */
	Lcd_Cmd_Set(0x0c);		/* display on, cursor off, blink off */
	Delay_ms(5);				/* 1msec delay */
	Lcd_Cmd_Set(0x1c);		/* shift display, right shift */
	Delay_ms(5);				/* 1msec delay */
	Lcd_Cmd_Set(0x06);		/* increment */
	Delay_ms(5);

	Lcd_Clear();
}

void Lcd_Clear(void)
{
	Lcd_Cmd_Set(0x01);		/* clear display */
	Delay_ms(2);				/* 2msec delay */  
}

void Lcd_Nibble_Cmd_Set(u8 Data)
{
	LCD_RS_L;
	Lcd_DataPort_Output(Data);

	Delay_us(50);
	LCD_E_H;
	Delay_us(50);
	LCD_E_L;
	Delay_us(50);
	Delay_us(50);
}

void Lcd_Cmd_Set(u8 Data)
{
	LCD_RS_L;
	Lcd_DataPort(Data);
}
void Lcd_Dis_Addr(u8  addr)		/* lcd display address ouput */
{
	Lcd_Cmd_Set(addr | 0x80);	/* address cmd bit set */
	Delay_ms(2);			/* 1msec delay */
}
void Lcd_Dis_Data(u8 Data)
{
	LCD_RS_H;
	Lcd_DataPort(Data);
}

void Lcd_DataPort(u8 Data)
{
	Lcd_DataPort_Output(Data);
	Delay_us(50);
	LCD_E_H;
	Delay_us(50);
	LCD_E_L;
	Delay_us(50);

	Lcd_DataPort_Output(Data<<4);
	Delay_us(50);
	LCD_E_H;
	Delay_us(50);
	LCD_E_L;
	Delay_us(50);
	Delay_us(50);
}

void Lcd_DataPort_Output(u8 Data)
{
	if(Data & 0x10)LCD_D4_H;
	else 		  LCD_D4_L;

	if(Data & 0x20)LCD_D5_H;
	else 		  LCD_D5_L;

	if(Data & 0x40)LCD_D6_H;
	else 		  LCD_D6_L;

	if(Data & 0x80)LCD_D7_H;
	else 		  LCD_D7_L;
}

void Lcd_String_Write(u8 addr,u8 *str)
{
	Lcd_Dis_Addr(addr);

	while(0 != *str)
	{
		Lcd_Dis_Data(*str);
		str++;
	}
}
void Lcd_Length_Write(u8 addr,u8 *str, u8 length)
{
	Lcd_Dis_Addr(addr);
	for(u8 i=0;i<length;i++)Lcd_Dis_Data(str[i]);
}

void Lcd_Char_Write(u8 addr, u8 c)
{
	Lcd_Dis_Addr(addr);
	Lcd_Dis_Data(c);
}





/*******************************************************************************
* Function Name  : ALive_Cpu
* Description    : Configurate the USART INT
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ALive_Cpu(void)
{			
	//u16 u16_Temp;
	
	if(gu16ALive_Cpu_Dly)return;

///////////////////////////////////////////////////////////////////////////////////

	if(gu8_Check_Led) CHECKLED_TOGGLE;
	else				  CHECKLED_OFF;
	
///////////////////////////////////////////////////////////////////////////////////

      gu16ALive_Cpu_Dly = 100;
}





/***********************************************************************
 	Function Name  : Key_Press_Check_Task
 	Parameter      : void
 	Returned Value : void
 	Comments       : Key_Press_Check_Task
***********************************************************************/
void Key_Press_Check_Task(void)
{	
///////////////////////////////////////////////////////////////////////////////////
	if(!READ_START)
	{
		if(gu8_fStart_Enable)
		{
			if(gu8_Start_Chat>KEY_CHATTER_MAX)
			{
				gu8_fStart=1;
	
				gu8_fStart_Enable = 0;
			}
			else
			{
				gu8_Start_Chat++;
			}
		}
	}
	else
	{
		gu8_Start_Chat = 0;
		gu8_fStart_Enable = 1;
                gu8_fStart = 0;
	}
///////////////////////////////////////////////////////////////////////////////////
	if(!READ_STOP)
	{
		if(gu8_fStop_Enable)
		{
			if(gu8_Stop_Chat>KEY_CHATTER_MAX)
			{
				gu8_fStop=1;	
	
				gu8_fStop_Enable = 0;
			}
			else
			{
				gu8_Stop_Chat++;
			}
		}
	}
	else
	{
		gu8_Stop_Chat = 0;
		gu8_fStop_Enable = 1;
                gu8_fStop = 0;
	}
///////////////////////////////////////////////////////////////////////////////////
}






/***********************************************************************
 	Function Name  : Key_Process_Task
 	Parameter      : void
 	Returned Value : void
 	Comments       : Key_Process_Task
***********************************************************************/
void Key_Process_Task(void)
{	if(gu8_Clock_setting_mode != 0)
        {
             LCD_print();
             if(gu8_fStart)
              {
                     gu8_fStart = 0;
                      gu8_Clock_setting_mode++;

                     if(gu8_Clock_setting_mode > 0x0A)
                     {
                        Lcd_Initial();
                        gu8_Clock_setting_mode = 0;
                        gu16_clock_sec_timer = (gu8_hour*3600)+(gu8_min*60)+gu8_sec;
                        gu16_year_counter = gu8_year1*1000+gu8_year2*100+gu8_year3*10+gu8_year4;
                     }
              }
              
             else if(gu8_fStop)
              {
                    gu8_fStop = 0;
                    Clock_Count_Check();
                    Clock_Setting();
              }
        }
        else
        {
            if((gu8_fStart==1)&&(gu8_fStop==1))
            {
                    gu8_Clock_setting_mode = 1;
                    gu8_fStart = 0;
                    gu8_fStop = 0;
            }
        }
        
   
	
}






/***********************************************************************
 	Function Name  : Clock_Setting
 	Parameter      : void
 	Returned Value : void
 	Comments       : Clock_Setting
***********************************************************************/
void Clock_Setting(void)
{
    switch(gu8_Clock_setting_mode)
    {
        case 1:     gu8_year1 = (gu8_year1+1)%10;       break;
        case 2:     gu8_year2 = (gu8_year2+1)%10;       break;
        case 3:     gu8_year3 = (gu8_year3+1)%10;       break;
        case 4:     gu8_year4 = (gu8_year4+1)%10;       break;
        case 5:     gu8_month = ((gu8_month+1)%13);       break;
        case 6:     gu8_day = (gu8_day+1)%gu8_dayset; break;
        case 7:     gu8_date = (gu8_date+1)%7;       break;
        case 8:     gu8_hour = (gu8_hour+1)%24;       break;
        case 9:     gu8_min = (gu8_min+1)%60;       break;
        case 10:    gu8_sec = (gu8_sec+1)%60;       break;
    }
    Clock_Count_Check();
    LCD_print();
}






/***********************************************************************
 	Function Name  : LCD_print
 	Parameter      : void
 	Returned Value : void
 	Comments       : LCD_print
***********************************************************************/
void LCD_print(void)
{
  if(gu8_Clock_setting_mode != 0)
  {
        if(gu16_Setting_Step_Dly == 0)
        {
            gu16_Setting_Step_Dly = 500;
            Lcd_Setting_Print_Set();
            Lcd_Length_Write(0x00, (u8 *)gu8_Str1,16);
            Lcd_Length_Write(0x40, (u8 *)gu8_Str2,16);
        }
  }
  else
  {
            sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10);
            sprintf(gu8_Str2, "  %3s %d%d:%d%d:%d%d  ",gu8_date_str, gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); 
            Lcd_Length_Write(0x00, (u8 *)gu8_Str1,16);
            Lcd_Length_Write(0x40, (u8 *)gu8_Str2,16);
  }
} 






/***********************************************************************
 	Function Name  : Lcd_Setting_Print_Set
 	Parameter      : void
 	Returned Value : void
 	Comments       : Lcd_Setting_Print_Set
***********************************************************************/
void Lcd_Setting_Print_Set(void)
{

      
      switch(gu8_Clock_setting_mode)
      {
          case 1:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str1, "    %d%d%d/%d%d/%d%d   ",gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
              else                                        { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
            }
            break;
          case 2:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str1, "   %d %d%d/%d%d/%d%d   ",gu8_year1,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
            }
            break;
          case 3:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str1, "   %d%d %d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
            }
            break;
          case 4:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str1, "   %d%d%d /%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
            }
            break;
          case 5:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str1, "   %d%d%d%d/  /%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_day/10,gu8_day%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
            }
            break;
          case 6:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/     ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10); }
            }
            break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
          case 7:
            {
              if(gu8_Clock_setting_toggle !=0)   
              { 
                    gu8_Clock_setting_toggle = 0; 
                    sprintf(gu8_Str1, "   %d%d%d%d/%d%d/%d%d   ",gu8_year1,gu8_year2,gu8_year3,gu8_year4,gu8_month/10,gu8_month%10,gu8_day/10,gu8_day%10);
                    sprintf(gu8_Str2, "      %d%d:%d%d:%d%d  ", gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); 
              }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str2, "  %3s %d%d:%d%d:%d%d  ",gu8_date_str, gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); }
            }
            break;
          case 8:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str2, "  %3s   :%d%d:%d%d  ",gu8_date_str,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str2, "  %3s %d%d:%d%d:%d%d  ",gu8_date_str, gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); }
            }
            break;
          case 9:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str2, "  %3s %d%d:  :%d%d  ",gu8_date_str, gu8_hour/10,gu8_hour%10 , gu8_sec/10,gu8_sec%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str2, "  %3s %d%d:%d%d:%d%d  ",gu8_date_str, gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); }
            }
            break;
          case 10:
            {
              if(gu8_Clock_setting_toggle !=0)   { gu8_Clock_setting_toggle = 0; sprintf(gu8_Str2, "  %3s %d%d:%d%d:    ",gu8_date_str, gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10); }
              else                                         { gu8_Clock_setting_toggle = 1; sprintf(gu8_Str2, "  %3s %d%d:%d%d:%d%d  ",gu8_date_str, gu8_hour/10,gu8_hour%10 ,gu8_min/10,gu8_min%10, gu8_sec/10,gu8_sec%10); }
            }
            break;
      
      }
      
      
}





/***********************************************************************
 	Function Name  : Clock_count
 	Parameter      : void
 	Returned Value : void
 	Comments       : Clock_count
***********************************************************************/
void Clock_count(void)
{
    if(gu8_Clock_setting_mode == 0)
    {
        if(gu16_Run_Step_Dly == 0)
        {
              gu16_Run_Step_Dly = 1000;
              gu16_clock_sec_timer++;
              gu8_sec = gu16_clock_sec_timer%60;
              gu8_min = (gu16_clock_sec_timer/60)%60;
              gu8_hour= (gu16_clock_sec_timer/3600)%24;
              if((gu8_hour == 0)&&(gu8_min == 0)&&(gu8_sec == 0))
              {
                  gu16_clock_sec_timer = 0 ;
                  gu8_date = (gu8_date + 1)%7;
                  Clock_Count_Check();
                  gu8_day = (gu8_day + 1)%gu8_dayset;
              
                  if(gu8_day == 0)
                  {
                      gu8_day = 1;
                      gu8_month = (gu8_month+1)%13;
                  }
                  if(gu8_month == 0 )
                  {
                      gu8_month = 1;
                      gu16_year_counter += 1;
                      gu8_year1 = gu16_year_counter/1000;
                      gu8_year2 = gu16_year_counter/100%10;
                      gu8_year3 = gu16_year_counter/10%10;
                      gu8_year4 = gu16_year_counter%10;
                  }
              }
              LCD_print();
        }
    }
    else
    {
          gu16_clock_sec_timer = 0;
    }
}

/***********************************************************************
 	Function Name  : Clock_Count_Check
 	Parameter      : void
 	Returned Value : void
 	Comments       : Clock_Count_Check
***********************************************************************/
void Clock_Count_Check(void)
{
      if((gu8_month == 1)||(gu8_month == 3)||(gu8_month == 5)||(gu8_month == 7)||(gu8_month == 8)||(gu8_month == 10)||(gu8_month == 12))
        gu8_dayset = 32;
      else if(gu8_month == 2)  
        gu8_dayset = 29;
      else
        gu8_dayset = 31;
      if(gu8_year1 == 0)
        gu8_year1 = 1;
      if(gu8_month == 0 )
        gu8_month = 1;
      if(gu8_day == 0)
        gu8_day = 1;
      
       switch(gu8_date)
       {
            case 0: sprintf(gu8_date_str,"Mon");                    break;
            case 1: sprintf(gu8_date_str,"Tue");                     break;
            case 2: sprintf(gu8_date_str,"Wen");                    break;
            case 3: sprintf(gu8_date_str,"Thu");                     break;
            case 4: sprintf(gu8_date_str,"Fri");                       break;
            case 5: sprintf(gu8_date_str,"Sat");                      break;
            case 6: sprintf(gu8_date_str,"Sun");                     break;
       }
}

