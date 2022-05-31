/*************************************************************
//	dsp program
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
#include "dsp.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "io_macros.h"

unsigned char DisplayData[128];				//Display Data
unsigned char DisplayTransData[128];			//Display Trans Data
unsigned char DisplayTransCount;			//Display Trans Count
unsigned char DisplayChecksum;				//Display Checksum

unsigned char LCDAddress;					//LCD Address
unsigned char LCDData;						//LCD Data




/***************** LCD Display table define **********************/
const unsigned char VERSION1_TBL[] =	{"       Rev1.00      "};
const unsigned char VERSION2_TBL[] =	{"                    "};
const unsigned char VERSION3_TBL[] =	{" Cathodic Disbonding"};
const unsigned char VERSION4_TBL[] =	{"       Tester       "};

const unsigned char CATHODIC_TEST_CH1_TBL[] =	{"CH1[0.000]V[  0.0]mA"};
const unsigned char CATHODIC_TEST_CH2_TBL[] =	{"CH2[0.000]V[  0.0]mA"};
const unsigned char CATHODIC_TEST_CH3_TBL[] =	{"CH3[0.000]V[  0.0]mA"};
const unsigned char CATHODIC_TEST_CH4_TBL[] =	{"CH4[0.000]V[  0.0]mA"};

const unsigned char SET_CH1_TEST_VOLT_TBL[] =	{"CH1:        [0.000]V"};
const unsigned char SET_CH2_TEST_VOLT_TBL[] =	{"CH2:        [0.000]V"};
const unsigned char SET_CH3_TEST_VOLT_TBL[] =	{"CH3:        [0.000]V"};
const unsigned char SET_CH4_TEST_VOLT_TBL[] =	{"CH4:        [0.000]V"};

const unsigned char SETSEL_CH1_TEST_VOLT_TBL[] =	{"CH1: ---->  [0.000]V"};
const unsigned char SETSEL_CH2_TEST_VOLT_TBL[] =	{"CH2: ---->  [0.000]V"};
const unsigned char SETSEL_CH3_TEST_VOLT_TBL[] =	{"CH3: ---->  [0.000]V"};
const unsigned char SETSEL_CH4_TEST_VOLT_TBL[] =	{"CH4: ---->  [0.000]V"};

const unsigned char SET_CH1_TEST_CURRENT_TBL[] =	{"CH1:       [  0.0]mA"};
const unsigned char SET_CH2_TEST_CURRENT_TBL[] =	{"CH2:       [  0.0]mA"};
const unsigned char SET_CH3_TEST_CURRENT_TBL[] =	{"CH3:       [  0.0]mA"};
const unsigned char SET_CH4_TEST_CURRENT_TBL[] =	{"CH4:       [  0.0]mA"};

const unsigned char SETSEL_CH1_TEST_CURRENT_TBL[] =	{"CH1: --->  [  0.0]mA"};
const unsigned char SETSEL_CH2_TEST_CURRENT_TBL[] =	{"CH2: --->  [  0.0]mA"};
const unsigned char SETSEL_CH3_TEST_CURRENT_TBL[] =	{"CH3: --->  [  0.0]mA"};
const unsigned char SETSEL_CH4_TEST_CURRENT_TBL[] =	{"CH4: --->  [  0.0]mA"};

const unsigned char SET_CH1_DISPOFFSET_VOLT_TBL[] =	{"CH1-DV:     [  0.0]%"};
const unsigned char SET_CH2_DISPOFFSET_VOLT_TBL[] =	{"CH2-DV:     [  0.0]%"};
const unsigned char SET_CH3_DISPOFFSET_VOLT_TBL[] =	{"CH3-DV:     [  0.0]%"};
const unsigned char SET_CH4_DISPOFFSET_VOLT_TBL[] =	{"CH4-DV:     [  0.0]%"};

const unsigned char SETSEL_CH1_DISPOFFSET_VOLT_TBL[] =	{"CH1-DV: --> [  0.0]%"};
const unsigned char SETSEL_CH2_DISPOFFSET_VOLT_TBL[] =	{"CH2-DV: --> [  0.0]%"};
const unsigned char SETSEL_CH3_DISPOFFSET_VOLT_TBL[] =	{"CH3-DV: --> [  0.0]%"};
const unsigned char SETSEL_CH4_DISPOFFSET_VOLT_TBL[] =	{"CH4-DV: --> [  0.0]%"};

const unsigned char SET_CH1_DISPOFFSET_CURRENT_TBL[] =	{"CH1-DA:     [  0.0]%"};
const unsigned char SET_CH2_DISPOFFSET_CURRENT_TBL[] =	{"CH2-DA:     [  0.0]%"};
const unsigned char SET_CH3_DISPOFFSET_CURRENT_TBL[] =	{"CH3-DA:     [  0.0]%"};
const unsigned char SET_CH4_DISPOFFSET_CURRENT_TBL[] =	{"CH4-DA:     [  0.0]%"};

const unsigned char SETSEL_CH1_DISPOFFSET_CURRENT_TBL[] =	{"CH1-DA: --> [  0.0]%"};
const unsigned char SETSEL_CH2_DISPOFFSET_CURRENT_TBL[] =	{"CH2-DA: --> [  0.0]%"};
const unsigned char SETSEL_CH3_DISPOFFSET_CURRENT_TBL[] =	{"CH3-DA: --> [  0.0]%"};
const unsigned char SETSEL_CH4_DISPOFFSET_CURRENT_TBL[] =	{"CH4-DA: --> [  0.0]%"};

const unsigned char SET_CH1_FBOFFSET_CURRENT_TBL[] =	{"CH1-FA:     [  0.0]%"};
const unsigned char SET_CH2_FBOFFSET_CURRENT_TBL[] =	{"CH2-FA:     [  0.0]%"};
const unsigned char SET_CH3_FBOFFSET_CURRENT_TBL[] =	{"CH3-FA:     [  0.0]%"};
const unsigned char SET_CH4_FBOFFSET_CURRENT_TBL[] =	{"CH4-FA:     [  0.0]%"};

const unsigned char SETSEL_CH1_FBOFFSET_CURRENT_TBL[] =	{"CH1-FA: --> [  0.0]%"};
const unsigned char SETSEL_CH2_FBOFFSET_CURRENT_TBL[] =	{"CH2-FA: --> [  0.0]%"};
const unsigned char SETSEL_CH3_FBOFFSET_CURRENT_TBL[] =	{"CH3-FA: --> [  0.0]%"};
const unsigned char SETSEL_CH4_FBOFFSET_CURRENT_TBL[] =	{"CH4-FA: --> [  0.0]%"};

const unsigned char SET_SETUP_START_VOLT_TBL[] =	{"START:      [0.000]V"};
const unsigned char SET_SETUP_MIN_CURRENT_TBL[] =	{"MIN-A:     [  0.0]mA"};
const unsigned char SET_SETUP_MAX_CURRENT_TBL[] =	{"MAX-A:     [  0.0]mA"};
const unsigned char SET_SETUP_MIN_SENSE_TBL[] =	{"MIN-S:     [  0.0]mA"};

const unsigned char SETSEL_SETUP_START_VOLT_TBL[] =	{"START: -->  [0.000]V"};
const unsigned char SETSEL_SETUP_MIN_CURRENT_TBL[] =	{"MIN-A: --> [  0.0]mA"};
const unsigned char SETSEL_SETUP_MAX_CURRENT_TBL[] =	{"MAX-A: --> [  0.0]mA"};
const unsigned char SETSEL_SETUP_MIN_SENSE_TBL[] 	=	{"MIN-S: --> [  0.0]mA"};

const unsigned char SET_ZERO_OFFSET_SET_TBL[] =	{" <ZERO OFFSET SET>  "};
const unsigned char SET_ZERO_OFFSET_YES_TBL[] =	{"        [YES]       "};
const unsigned char SET_ZERO_OFFSET_NO_TBL[] =	{"        [NO]        "};

const unsigned char BLANK_TBL[] =		{"                    "};


/*************************************************************
//	LCD display data set
//	------------------------------------------------
//	Input : Ddata
//	Output:
**************************************************************/
void LCD_dis_data(unsigned char Ddata)
{
	DisplayData[LCDAddress] = Ddata;
	LCDAddress++;
}

/*************************************************************
//	LCD display address set
//	------------------------------------------------
//	Input : command
//	Output:
**************************************************************/
void LCD_dis_add(unsigned char Dadd)
{
	LCDAddress = Dadd;
}

/*************************************************************
//	LCD any display
//	------------------------------------------------
//	Input :
//	Output:
**************************************************************/
void LCD_any_display(unsigned char Dadd, unsigned char const *Dstr)
{
	unsigned char Count=0;
	
	LCD_dis_add(Dadd); 						//address output
	while(Dstr[Count] != NULL && Count != 40)
	{
		LCD_dis_data(Dstr[Count]); 				//string data output
		Count++;
   	}
}

/*************************************************************
//	LCD all display
//	------------------------------------------------
//	Input :
//	Output:
**************************************************************/
void LCD_all_display(unsigned char const  *Dstr)
{
	LCD_any_display(0, Dstr);
	LCD_any_display(40, Dstr + 40);
}

/*************************************************************
//	Display Data Update
//	------------------------------------------------
//	Input :
//	Output:
**************************************************************/
void Display_Data_Update(void)
{
	unsigned char Count;

	for (Count = 0; Count < 96; Count++)
	{
		DisplayTransData[Count] = DisplayData[Count];
	}
}
