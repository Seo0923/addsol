/*************************************************************
//	mmi program
//	------------------------------------------------------
//	Project Name : Cathodic Debonding Tester
//	Model Name  : ACT-100M
//	Start Date  : 2016.06.17
//	Chip Number : STM32F103VGT
//	C-Compiler	: EWARM
//	Written by 	: jhKim
//  COPYRIGHT (c) 2010 AddSol All rights reserved.
**************************************************************/

#ifndef __MMI_H__
#define __MMI_H__

//		Fuction Mode
#define INITIAL_MODE						0			//Initial Mode
#define CATHODIC_DISBONDING_MODE		1			//Cathodic Disbonding Mode

#define SET_TEST_VOLT_MODE				2			//Set Test Volt Mode
#define SET_TEST_CURRENT_MODE			3			//Set Test Current Mode

#define INTERNAL_VOLT_CURRENT_VIEW_MODE	4			//Internal Volt/Current View Mode
#define SET_DISPVOLT_OFFSET_MODE			5			//Set Display Voltage Offset Mode
#define SET_DISPCURRENT_OFFSET_MODE		6			//Set Display Current Offset Mode
#define SET_FBCURRENT_OFFSET_MODE		7			//Set Feedback Current Offset Mode
#define SET_ZERO_OFFSET_SET_MODE			8			//Set Zero Offset Mode


#define LIMIT_TIME_10S		10
#define LIMIT_TIME_30S		30
#define LIMIT_TIME_60S		60

#define CH1		0
#define CH2		1
#define CH3		2
#define CH4		3

#define CHE1		0
#define CHE2		1
#define CHE3		2
#define CHE4		3

#define CHA1		10
#define CHA2		11
#define CHA3		12
#define CHA4		13

#define ADC_INITAL_E_G1	0x8c					//15SPS		//16Bit(15Bit)
#define ADC_INITAL_A_G1	0x8c					//15SPS		//16Bit(15Bit)

#define ADS1110_WR		0x00
#define ADS1110_RD		0x01
#define ADS1110_ADD		0x90

#define DAC_MIN_V		500
#define DAC_MAX_V		9999

#define PWM_MAX			1500

#define CHMAXCOUNT		4

#define ADCGAIN1_STEP      0.0000625;

#define FBVOLT_MAX 	9.99
#define ADSVOLT_MAX 9.99



#define SET_CURRENT_MIN	10
#define SET_CURRENT_MAX	1500

#define SET_VOLT_MIN	1000
#define SET_VOLT_MAX	5000


#define FLASHSTARTADD ((unsigned long)0x0807F800)
#define FLASHENDADD ((unsigned long)0x0807FFFF)


#define FLASH_MARK			60					//New FLASH mark
#define FLASH_MARK_VALUE		0x5a5a				//New FLASH mark value


extern unsigned char FunctionMode;					//Function Mode
extern unsigned char NewMode;						//New Mode

extern unsigned short DisplayVolt[4];					//Display Voltage
extern unsigned short DisplayAmpare[4];				//Display Ampare

extern unsigned char CHSenseStatus[4];				//CH Sense Status

extern unsigned char ADC_STM32F103_Interval;		//ADC STM32F103 Interval

extern unsigned short FeedbackVolt[4];				//Feedback Voltage
extern unsigned short FeedbackAmpare[4];				//Feedback Ampare


extern unsigned short CH1PWMValue;					//CH1 PWM Value
extern unsigned short CH2PWMValue;					//CH2 PWM Value
extern unsigned short CH3PWMValue;					//CH3 PWM Value
extern unsigned short CH4PWMValue;					//CH4 PWM Value
extern unsigned short SetVoltage[4];					//Set Voltage

extern unsigned short FunctionLimitTime;				//Function Limit Time

extern unsigned short Parameter_Data[50];			//Parameter Data

extern const unsigned short PARAMETER_INITIAL_TBL[];


void Function_Mode_Service(void);

void Host_RS232C_Data_Receive_svc(void);
void Host_Cathodic_Disbonding_Data_Trans_svc(void);
void Host_Current_Setup_Data_Trans_svc(void);

void ADS_Read_Value_to_Calculate_svc(void);

void OffSet_Value_Display_svc(unsigned char Address, unsigned short OffData);
void Voltage_Display_svc(unsigned char Address, unsigned short VData);
void Current_Display_svc(unsigned char Address, unsigned short CData);

void Auto_Feedback_Voltage_Adjust_svc(void);
void Set_Voltage_Data_Initial_Set(void);
void Volt_ADS_Gain_Data_Initial_Set(void);
void Ampare_ADS_Gain_Data_Initial_Set(void);
void ADC_STM32F103_Read_to_Calculate_svc(void);

unsigned char ADS1110_Data_Write_Svc(unsigned char Channel , unsigned char SetData);
unsigned char ADS1110_Data_Read_Svc(unsigned char Channel , unsigned short *ADValue);

unsigned CH1E_Read_Byte_svc(void);
unsigned CH1A_Read_Byte_svc(void);
unsigned CH2E_Read_Byte_svc(void);
unsigned CH2A_Read_Byte_svc(void);
unsigned CH3E_Read_Byte_svc(void);
unsigned CH3A_Read_Byte_svc(void);
unsigned CH4E_Read_Byte_svc(void);
unsigned CH4A_Read_Byte_svc(void);

void Flash_Parameter_Read(void);
void Flash_Parameter_Write(void);
void Flash_Parameter_Initial(void);
void Flash_Word_Write(unsigned short Address, unsigned short WData);
unsigned short Flash_Word_Read(unsigned short Address);

void ADS1110_Delay_Time(void);


#endif /*__MMI_H__*/

