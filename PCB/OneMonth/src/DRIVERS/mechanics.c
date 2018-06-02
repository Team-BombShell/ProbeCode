/*
 * mechanics.c
 *
 * Created: 5/31/2018 6:22:03 PM
 *  Author: Mason
 */ 

#include "mechanics.h"
#include <asf.h>

void heatshield_servo(void){
	PORTE.OUT = 0b00000001;
}

void heatshield_solenoid(void){
	PORTA.OUT = 0b10000000;
}
