#ifndef TINY_USART_H_
#define TINY_USART_H_


// initialize USART to 9600 baud and 8N1
// (!) interrupts must be globally disabled
void usart_init(void);


// 1 if transmitter has completed all transfers, no new data in transmit buffer (UDR)
// the TXC flag must be cleared before each transmission
unsigned char txComplete(void);


// 1 if transmit buffer (UDR) is empty, and therefore ready to be written
unsigned char txReady(void);


// 1 if data are available to read, 0 if no unread data in the receive buffer
unsigned char rxAvailable(void);


// transmits a byte, based on polling the Data Register Empty (UDRE) flag
void usart_write(unsigned char data);


// receives a byte, based on polling the Receive Complete (RXC) flag
unsigned char usart_read(void);


// flush during normal operation, reads UDR until RXC flag is cleared
void usart_flush(void);


// transmits a string
void usart_write_s(unsigned char *str);


// receives a string until the eol or buf_max
void usart_read_until_s(unsigned char *buf, int buf_max, unsigned char eol);


#endif
