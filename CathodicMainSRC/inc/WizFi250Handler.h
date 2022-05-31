#ifndef	_WizFi250HANDLER_H
#define	_WizFi250HANDLER_H

#include <stdint.h>

/*
#define uint8_t  	unsigned char
#define int8_t 	signed char
#define uint32_t 	unsigned long
#define int32_t  	long
*/
uint8_t	send_and_check_command	(char* send_command, uint8_t cr_lf, uint32_t check_delay, uint32_t check_count, char* str_find1, char* str_find2, uint8_t debug_print);
void	WizFi250_Restart	();
void	WizFi250_FactoryReset	();
int8_t  sendDataInCommandMode	(uint32_t size);
//void wizfi250_resp_thread(void * pvParameters);
//
//void WizFi250_Restart();
//void WizFi250_FactoryReset ();

#endif	//_WizFi250HANDLER_H
