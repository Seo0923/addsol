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

#ifndef __DSP_H__
#define __DSP_H__

#define DISP_HEAD		0

#define DISP_LCD100		1
#define DISP_LCD101		2
#define DISP_LCD102		3
#define DISP_LCD103		4
#define DISP_LCD104		5
#define DISP_LCD105		6
#define DISP_LCD106		7
#define DISP_LCD107		8
#define DISP_LCD108		9
#define DISP_LCD109		10
#define DISP_LCD110		11
#define DISP_LCD111		12
#define DISP_LCD112		13
#define DISP_LCD113		14
#define DISP_LCD114		15
#define DISP_LCD115		16
#define DISP_LCD116		17
#define DISP_LCD117		18
#define DISP_LCD118		19
#define DISP_LCD119		20

#define DISP_LCD300		21
#define DISP_LCD301		22
#define DISP_LCD302		23
#define DISP_LCD303		24
#define DISP_LCD304		25
#define DISP_LCD305		26
#define DISP_LCD306		27
#define DISP_LCD307		28
#define DISP_LCD308		29
#define DISP_LCD309		30
#define DISP_LCD310		31
#define DISP_LCD311		32
#define DISP_LCD312		33
#define DISP_LCD313		34
#define DISP_LCD314		35
#define DISP_LCD315		36
#define DISP_LCD316		37
#define DISP_LCD317		38
#define DISP_LCD318		39
#define DISP_LCD319		40

#define DISP_LCD200		41
#define DISP_LCD201		42
#define DISP_LCD202		43
#define DISP_LCD203		44
#define DISP_LCD204		45
#define DISP_LCD205		46
#define DISP_LCD206		47
#define DISP_LCD207		48
#define DISP_LCD208		49
#define DISP_LCD209		50
#define DISP_LCD210		51
#define DISP_LCD211		52
#define DISP_LCD212		53
#define DISP_LCD213		54
#define DISP_LCD214		55
#define DISP_LCD215		56
#define DISP_LCD216		57
#define DISP_LCD217		58
#define DISP_LCD218		59
#define DISP_LCD219		60

#define DISP_LCD400		61
#define DISP_LCD401		62
#define DISP_LCD402		63
#define DISP_LCD403		64
#define DISP_LCD404		65
#define DISP_LCD405		66
#define DISP_LCD406		67
#define DISP_LCD407		68
#define DISP_LCD408		69
#define DISP_LCD409		70
#define DISP_LCD410		71
#define DISP_LCD411		72
#define DISP_LCD412		73
#define DISP_LCD413		74
#define DISP_LCD414		75
#define DISP_LCD415		76
#define DISP_LCD416		77
#define DISP_LCD417		78
#define DISP_LCD418		79
#define DISP_LCD419		80

#define DISP_LEDDATA		81

#define LCDLINE1				DISP_LCD100
#define LCDLINE2				DISP_LCD200
#define LCDLINE3				DISP_LCD300
#define LCDLINE4				DISP_LCD400

extern unsigned char DisplayData[128];			//Display Data
extern unsigned char DisplayTransData[128];		//Display Trans Data
extern unsigned char DisplayTransCount;			//Display Trans Count
extern unsigned char DisplayChecksum;			//Display Checksum

extern unsigned char LCDAddress;				//LCD Address
extern unsigned char LCDData;					//LCD Data

extern const unsigned char VERSION1_TBL[];
extern const unsigned char VERSION2_TBL[];
extern const unsigned char VERSION3_TBL[];
extern const unsigned char VERSION4_TBL[];

extern const unsigned char CATHODIC_TEST_CH1_TBL[];
extern const unsigned char CATHODIC_TEST_CH2_TBL[];
extern const unsigned char CATHODIC_TEST_CH3_TBL[];
extern const unsigned char CATHODIC_TEST_CH4_TBL[];

extern const unsigned char SET_CH1_TEST_VOLT_TBL[];
extern const unsigned char SET_CH2_TEST_VOLT_TBL[];
extern const unsigned char SET_CH3_TEST_VOLT_TBL[];
extern const unsigned char SET_CH4_TEST_VOLT_TBL[];

extern const unsigned char SETSEL_CH1_TEST_VOLT_TBL[];
extern const unsigned char SETSEL_CH2_TEST_VOLT_TBL[];
extern const unsigned char SETSEL_CH3_TEST_VOLT_TBL[];
extern const unsigned char SETSEL_CH4_TEST_VOLT_TBL[];

extern const unsigned char SET_CH1_TEST_CURRENT_TBL[];
extern const unsigned char SET_CH2_TEST_CURRENT_TBL[];
extern const unsigned char SET_CH3_TEST_CURRENT_TBL[];
extern const unsigned char SET_CH4_TEST_CURRENT_TBL[];

extern const unsigned char SETSEL_CH1_TEST_CURRENT_TBL[];
extern const unsigned char SETSEL_CH2_TEST_CURRENT_TBL[];
extern const unsigned char SETSEL_CH3_TEST_CURRENT_TBL[];
extern const unsigned char SETSEL_CH4_TEST_CURRENT_TBL[];

extern const unsigned char SET_CH1_DISPOFFSET_VOLT_TBL[];
extern const unsigned char SET_CH2_DISPOFFSET_VOLT_TBL[];
extern const unsigned char SET_CH3_DISPOFFSET_VOLT_TBL[];
extern const unsigned char SET_CH4_DISPOFFSET_VOLT_TBL[];

extern const unsigned char SETSEL_CH1_DISPOFFSET_VOLT_TBL[];
extern const unsigned char SETSEL_CH2_DISPOFFSET_VOLT_TBL[];
extern const unsigned char SETSEL_CH3_DISPOFFSET_VOLT_TBL[];
extern const unsigned char SETSEL_CH4_DISPOFFSET_VOLT_TBL[];

extern const unsigned char SET_CH1_DISPOFFSET_CURRENT_TBL[];
extern const unsigned char SET_CH2_DISPOFFSET_CURRENT_TBL[];
extern const unsigned char SET_CH3_DISPOFFSET_CURRENT_TBL[];
extern const unsigned char SET_CH4_DISPOFFSET_CURRENT_TBL[];

extern const unsigned char SETSEL_CH1_DISPOFFSET_CURRENT_TBL[];
extern const unsigned char SETSEL_CH2_DISPOFFSET_CURRENT_TBL[];
extern const unsigned char SETSEL_CH3_DISPOFFSET_CURRENT_TBL[];
extern const unsigned char SETSEL_CH4_DISPOFFSET_CURRENT_TBL[];

extern const unsigned char SET_CH1_FBOFFSET_CURRENT_TBL[];
extern const unsigned char SET_CH2_FBOFFSET_CURRENT_TBL[];
extern const unsigned char SET_CH3_FBOFFSET_CURRENT_TBL[];
extern const unsigned char SET_CH4_FBOFFSET_CURRENT_TBL[];

extern const unsigned char SETSEL_CH1_FBOFFSET_CURRENT_TBL[];
extern const unsigned char SETSEL_CH2_FBOFFSET_CURRENT_TBL[];
extern const unsigned char SETSEL_CH3_FBOFFSET_CURRENT_TBL[];
extern const unsigned char SETSEL_CH4_FBOFFSET_CURRENT_TBL[];

extern const unsigned char SET_SETUP_START_VOLT_TBL[];
extern const unsigned char SET_SETUP_MIN_CURRENT_TBL[];
extern const unsigned char SET_SETUP_MAX_CURRENT_TBL[];
extern const unsigned char SET_SETUP_MIN_SENSE_TBL[];

extern const unsigned char SETSEL_SETUP_START_VOLT_TBL[];
extern const unsigned char SETSEL_SETUP_MIN_CURRENT_TBL[];
extern const unsigned char SETSEL_SETUP_MAX_CURRENT_TBL[];
extern const unsigned char SETSEL_SETUP_MIN_SENSE_TBL[];

extern const unsigned char SET_ZERO_OFFSET_SET_TBL[];
extern const unsigned char SET_ZERO_OFFSET_YES_TBL[];
extern const unsigned char SET_ZERO_OFFSET_NO_TBL[];

extern const unsigned char  BLANK_TBL[];

void LCD_dis_data(unsigned char Ddata);
void LCD_dis_add(unsigned char Dadd);
void LCD_any_display(unsigned char Dadd, unsigned char const *Dstr);
void LCD_all_display(unsigned char const  *Dstr);
void Display_Data_Update(void);




#endif /*__DSP_H__*/

