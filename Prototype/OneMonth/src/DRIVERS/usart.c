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


void openlogger_tx(float data[16]){
	
	//TODO: 
}

void xbee_tx(float data[16]){
	//TODO:
}