/*
 * GPS.c
 *
 * Created: 6/3/2018 8:30:02 PM
 *  Author: Mason
 */ 
#include "GPS.h"
#include <asf.h>

void init_GPS(void){
	
	PORTD.DIR |= 0b //LOL
	PORTD.DIR &= 0b //LOL cont.
	
	//Configure pins
	PORTD.DIR |= 0b //LOL 3.0
	
	
	sysclk_enable_peripheral_clock(&GPS_USART);
	
	static usart_serial_options_t usart_options = {
		.baudrate = 9600,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits = true,
	};
	
	usart_serial_init(&GPS_USART, &options);
}