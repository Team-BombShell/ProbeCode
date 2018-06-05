/*
 * mechanics.c
 *
 * Created: 5/31/2018 6:22:03 PM
 *  Author: Mason
 */ 

#include "mechanics.h"
#include <asf.h>

/*void heatshield_servo(void){
	PORTE.DIRSET = 0b00000001;
	PORTE.OUTSET = 0b00000001;
}*/

void heatshield_solenoid(void){
	PORTA.DIRSET = 0b10000000;
	PORTA.OUTSET = 0b10000000;
}

void hotwire (){
	PORTD.DIR |= 0b00000010;
	PORTD.OUT |= 0b00000010; //
	delay_ms(4000);
	PORTD.OUT &= 0b11111101;
}