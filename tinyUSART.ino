/*
 *
 *    a simple program for usage demonstration
 *
 *       does an echo check over serial communication
 *
 */



#include <avr/io.h>
#include "tiny_usart.h"


#define MAX_BUF 16


int main(void)
{
	usart_init();

	unsigned char buf[MAX_BUF];
	unsigned char eol = '%';

	while(1)
	{
		if( rxAvailable() )
		{
			usart_read_until_s(buf, MAX_BUF, eol);
			usart_write_s(buf);
		} 

 	}


	return 0;
}
