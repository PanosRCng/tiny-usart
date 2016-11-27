/*
 *    tiny_usart
 *
 *
 *
 *	- ATtiny2313 serial port library
 *
 *
 *	- sets the serial communication to 9600 Baud rate and 
 *	  8N1 (8data, No parity, 1stop bit)
 *
 *
 *
 *  	- developed (and tested) for a ATtiny2313 running 
 *	  at 8 MHz from its internal oscillator
 */




#include <avr/io.h>
#include "tiny_usart.h"


#define BAUD 9600
#define MYUBRR ((F_CPU / (BAUD * 16L)) - 1)



void usart_init(void)
{
 	// set baud rate
	UBRRH = (unsigned char)( MYUBRR >> 8); 
	UBRRL = (unsigned char) MYUBRR; 

	// enable receiver and transmitter
	UCSRB = (1<<RXEN) | (1<<TXEN);

	// frame format: 8data, No parity, 1stop bit (8N1)
	// asynchronous operation using polling
	UCSRC = (3<<UCSZ0);  
}


void usart_write(unsigned char data)
{
	// wait for empty transmit buffer
	while( !txReady() )
	;
  
	// send data
	UDR = data;
}


unsigned char usart_read(void)
{
	// wait for data to be received
	while( !rxAvailable() )
	;

	// get received data
	return UDR;
}


void usart_write_s(unsigned char *str)
{
	while(*str)
	{
    		usart_write(*str++);
  	}
}


void usart_read_until_s(unsigned char *buf, int buf_max, unsigned char eol)
{
	int i = 0;
	unsigned char c;

	do
	{
		c = usart_read();
        	buf[i++] = c;
    	}
	while( (c != eol) && (i < buf_max) );

	buf[i] = '\0';
}


unsigned char rxAvailable(void)
{
	return (UCSRA & (1<<RXC));
}


unsigned char txComplete(void)
{
	return (UCSRA & (1<<TXC));
}


unsigned char txReady(void)
{
	return (UCSRA & (1<<UDRE));
}


void usart_flush(void)
{
	unsigned char dummy;
	while( rxAvailable )
	{
		dummy = UDR;
	}
}


