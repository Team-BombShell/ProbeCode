/*
 * usart.c
 *
 * Created: 9/7/2017 9:22:58 PM
 *  Author: Mason
 */ 
#include <asf.h>
#include "Drivers/usart_comms.h"
#include "register_definitions.h"
#include "Drivers/mechanics.h"
#include "DRIVERS/timer_counter.h"

//extern uint8_t state;
volatile char xbee_rx_temporary;

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
	PORTD.DIRSET = 0b00001000;	
	PORTD.DIRCLR = 0b00000100;
	PORTD.OUTSET = 0b00001000;
	
	//Sends bit over Openlogger
	PORTC.DIRSET = 0b00001000;
	PORTC.OUTSET = 0b00001000;
	
	
	stdio_serial_init(&USARTD0, &usart_options);
	usart_serial_init(&USARTC0, &openlogger_usart_options);
	
	USARTD0.CTRLA = 0b00010000;
}


void usart_tx(USART_t* usart_channel, const char* text, ...){
	char write_buffer[256];
	va_list args;
	va_start(args, text);
	vsprintf(write_buffer, text, args);
	va_end(args);
	write_buffer[255] = '!';
	
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
	
ISR(USARTD0_RXC_vect){
	//If we send reset things to the board
	xbee_rx_temporary = USARTD0.DATA;
	printf("We received %c\n", xbee_rx_temporary);
	switch(xbee_rx_temporary){
		case '!':						//reset MCU 
			wdt_reset_mcu();
			break;
		case '@':						//change to flight state 0
			state = 0;
			break;
		case '#':						//change to flight state 1
			state = 1;
			break;
		case '$':						//change to flight state 2
			state = 2;
			break;
		case '%':						//change to flight state 3
			state = 3;
			break;
		case '^':						//deploy heatshield
			heatshield_hotwire();
			break;
		case '&':						//deploy parachute and detatch heatshield
			heatshield_solenoid();
			break;
		case '*':						//detatching heatshield
			heatshield_detatch_hotwire();
			break;
		case '(':						//buzzer on
			buzzer_counter_init(104, 50);
			break;
		case ')':						//buzzer off
			buzzer_counter_init(0, 0);
			break;
		case '_':						//camera on
			camera_on();
			break;
	}
	
}
