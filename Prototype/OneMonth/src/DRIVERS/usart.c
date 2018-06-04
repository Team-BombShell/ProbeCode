/*
 * usart.c
 *
 * Created: 9/7/2017 9:22:58 PM
 *  Author: Mason
 */ 
#include <asf.h>
#include "Drivers/usart.h"

void usart_init(void){
	
	//Initializes XBee
	static usart_serial_options_t usart_options = {
		.baudrate = 9600,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits = true
	};
	
	
	//Initialize the OpenLogger
	static usart_serial_options_t openlogger_usart_options = {
		.baudrate = 9600,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits = true
		
	};
	
	//Sends bit over Xbee
	PORTC.DIRSET = 0b00001000;	
	PORTC.OUTSET = 0b00001000;
	
	//Sends bit over Openlogger
	PORTD.DIRSET = 0b00001000;
	PORTD.OUTSET = 0b00001000;
	
	
	stdio_serial_init(&USARTC0, &usart_options);
	stdio_serial_init(&USARTD0, &openlogger_usart_options);
}


void usart_tx(USART_t* usart_channel, const char* text, ...){
	char write_buffer[256];
	va_list args;
	va_start(args, text);
	vsprintf(write_buffer, text, args);
	va_end(args);
	
	
	for(int i = 0; i < sizeof(write_buffer); i++)
	{
		usart_putchar(usart_channel, write_buffer[i]);
	}
}


char* usart_rx(USART_t* usart_channel, char* read_buffer){
	int loc = 0;
	while(usart_rx_is_complete(usart_channel))
	{
		read_buffer[loc] = usart_getchar(usart_channel);
		loc++;
		
	}
	return read_buffer;
}
	

