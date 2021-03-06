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

void heatshield_solenoid(PORT_t* port){
	(*port).DIRSET = 0b10000000;
	(*port).OUTSET = 0b10000000;
}

void heatshield_hotwire (void){
	PORTD.DIR |= 0b00000010;
	PORTD.OUT |= 0b00000010; //TODO: fix these port addresses
	delay_ms(4000);
	PORTD.OUT &= 0b11111101;
}

void parachute_hotwire (void) {
	PORTD.DIR |= 0b00000010;
	PORTD.OUT |= 0b00000010; //TODO: fix these port addresses
	delay_ms(4000);
	PORTD.OUT &= 0b11111101;
}

void heatshield_detatch_hotwire(void){
	PORTD.DIR |= 0b00000010;
	PORTD.OUT |= 0b00000010; //TODO: fix these port addresses
	delay_ms(4000);
	PORTD.OUT &= 0b11111101;	
}

void buzzer_on(void){
	PORTA.DIR |= 0b00001000;
	PORTA.OUT |= 0b00001000;
	
}
void buzzer_off(void){
	PORTA.DIR |= 0b00001000;
	PORTA.OUT &= 0b11110111;
	
}
void camera_on(void){
	PORTE.DIR |= 0b01000000;
	PORTE.OUT |= 0b01000000;
	
}
void camera_off(void){
	PORTE.DIR |= 0b01000000;
	PORTE.OUT &= 0b10111111;
	
}