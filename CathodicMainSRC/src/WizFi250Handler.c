#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "WizFi250Handler.h"
#include "uart.h"
#include "type.h"
//#include "common.h"


#include "includes.h"
#include "main.h"
#include "user.h"
#include "IOdefine.h"
#include "Uart.h"
#include "timer.h"
#include "mmi.h" 
#include "io_macros.h"
#include "dsp.h"


//extern xSemaphoreHandle RespSemaphore;
//extern xTaskHandle xHandle1;

#define BUFF_LEN 1024
uint8_t  g_wizfi250_resp_buff[BUFF_LEN]={0,};
uint32_t g_resp_data_len=0;



uint8_t send_and_check_command(char* send_command, uint8_t cr_lf, uint32_t check_delay, uint32_t check_count, char* str_find1, char* str_find2, uint8_t debug_print)
{
	uint32_t i;
	uint8_t is_found1=0, is_found2=0;
	uint32_t nResult = 0;
	int8_t ch;
	char crlf_string[3];
	
	g_resp_data_len = 0;
	
	// Send Command
	uart_puts(4,(uint8_t*)send_command,strlen(send_command));

	// Send CR, LF
	if ( cr_lf==1 )		strcpy(crlf_string, "\r");
	else if ( cr_lf==2 )	strcpy(crlf_string, "\n");
	else if ( cr_lf==3 )	strcpy(crlf_string, "\r\n");
	if ( cr_lf==1 || cr_lf==2 || cr_lf==3 )
	{
		uart_puts(4,(uint8_t*)crlf_string,strlen(crlf_string));
	}
	
	if ( debug_print==1 )	printf("\r\nDBG>>> Send : %s\r\n", send_command);
	// Recv Response
	if ( str_find1==0 ) is_found1 = 1;
	if ( str_find2==0 ) is_found2 = 1;
	printf("\r\nDBG>>> Resp Recv \r\n");

	for(i=0;i<check_count;i++)
	{
		do{
			ch = uart_getc_nonblk(4);
			if(ch != RET_NOK)
				g_wizfi250_resp_buff[g_resp_data_len++] = (uint8_t)ch;
			if(ch == '\n')
				break;
			
		}while(ch != RET_NOK);
		g_wizfi250_resp_buff[g_resp_data_len]='\0';
	
		if ( is_found1==0 )
		{
			if ( strstr((char*)g_wizfi250_resp_buff, str_find1) ) is_found1 = 1;
		}
		if ( is_found2==0 )
		{
			if ( strstr((char*)g_wizfi250_resp_buff, str_find2) ) is_found2 = 1;
		}
		
		if ( debug_print==1 )	printf("%s", g_wizfi250_resp_buff);
		g_resp_data_len = 0;

		if( is_found1 == is_found2 ) break;
		
		Delay_ms(check_delay);
		//Time_Delay_svc(check_delay);
	}


	// Error : Timeout or Not Found Success String
	if ( !(is_found1 && is_found2) )
	{
		printf("DBG>>> Error : Timeout or Not Found Success String\r\n");
		nResult = 2;
		return nResult;
	}

	
	return nResult;
}
/*
int8_t sendDataInCommandMode(uint32_t size)
{
	int8_t ch;
	uint32_t i;
	uint8_t buff_data = 'A';
	uint32_t total_send = 0;
	
	char send_size[10]={0,};
	uint8_t send_cmd[100]={0,};
	itoa(size, send_size, 10);
	
	g_resp_data_len = 0;
	
	// Send Command
	sprintf(send_cmd,"AT+SSEND=0,,,%s",(char*)send_size);
	uart_puts(1,(uint8_t*)send_cmd,strlen(send_cmd));
	uart_puts(1,(uint8_t*)"\r",1);
	//printf("\r\nDBG>>> Send : %s\r\n",(char*)send_size);

//	while(1)
//	{
//		ch = uart_getc_nonblk(1);
//		if(ch != RET_NOK)
//		{
//			g_wizfi250_resp_buff[g_resp_data_len++] = (uint8_t)ch;
//			if( strstr((char*)g_wizfi250_resp_buff,"[0,,,1024]"))
//			{
//				g_wizfi250_resp_buff[g_resp_data_len]='\0';
//				//printf("%s",g_wizfi250_resp_buff);
//				g_resp_data_len = 0;
//				break;
//			}
//		}
//	}
	for (i=0; i<size; i++)
	{
		uart_putc(1,buff_data);
		total_send++;
		if     ( buff_data=='z' )	buff_data = '\r';
		else if( buff_data=='\r' )	buff_data = '\n';
		else if( buff_data=='\n' )	buff_data = 'A';
		else if( i == size -3)		buff_data = '\r';
		else 				buff_data++;
	}

	for(i=0;i<1000;i++)
	{
		while(1)
		{
			ch = uart_getc_nonblk(1);
			if(ch != RET_NOK)
			{
				g_wizfi250_resp_buff[g_resp_data_len++] =(uint8_t)ch;
			}
			else
				break;
		}
		
		if( strstr((char*)g_wizfi250_resp_buff,"[OK]"))
		{
			g_wizfi250_resp_buff[g_resp_data_len]='\0';
//			printf("%s",g_wizfi250_resp_buff);
			g_resp_data_len = 0;
			break;
		}
		else if(strstr((char*)g_wizfi250_resp_buff,"[ERROR]"))
		{
			g_wizfi250_resp_buff[g_resp_data_len]='\0';
			printf("%s",g_wizfi250_resp_buff);
			g_resp_data_len = 0;
			return RET_NOK;
		}
		//Delay_ms(1);
	}
	
	return RET_OK;
}

*/
void WizFi250_Restart()
{
	WIFI_RESET_HIGH;
	Delay_ms(10);
	WIFI_RESET_LOW;
	Delay_ms(10);
	WIFI_RESET_HIGH;

}

void WizFi250_FactoryReset ()
{
	//gpio_set(GPIOC, GPIO_Pin_10, VAL_HIGH);
	WIFI_RESET_HIGH;
	Delay_ms(200);

	for(int i=0;i<3;i++)
	{
//		gpio_set(GPIOC, GPIO_Pin_10, VAL_LOW);
		WIFI_RESET_LOW;
		Delay_ms(200);
//		gpio_set(GPIOC, GPIO_Pin_10, VAL_HIGH);
		WIFI_RESET_HIGH;
		Delay_ms(200);
	}
}