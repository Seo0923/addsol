/*************************************************************************

							Copyright (C) 2012 Addsol

FILE NAME : User.h

CPU :  STM32F103ETS

Programer:    Janghwan Kim 

UPDATE :

2012. 02. 13. initial coding

*************************************************************************/

/* FLASH MEMORY DEFINE */
#define fls_page_no 	32
#define include_blk_size	3

#if 1
/*lcd 176 T 220 size*/
#define img_blk_size	8		// 176*220 = 8block	
#define img_start_blk	135		// 176*220 = 8block	

#define LCD_WIDTH	220
#define LCD_HEIGHT	176

#define RET_FAIL		1
#define RET_OK		0
#define RET_NOK		-1
#endif


