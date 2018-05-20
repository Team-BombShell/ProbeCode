/*
 * usart.c
 *
 * Created: 9/7/2017 9:22:58 PM
 *  Author: Mason
 */ 
#include <asf.h>
#include "Drivers/usart.h"

void usart_init(void){
	static usart_serial_options_t usart_options = {
		.baudrate = 9600,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits = true
	};
	
	PORTC.DIRSET = 0b00001000;
	PORTC.OUTSET = 0b00001000;
	
	stdio_serial_init(&USARTC0, &usart_options);
}