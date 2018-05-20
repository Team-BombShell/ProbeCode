/*
 * thermistor.c
 *
 * Created: 9/20/2017 9:11:51 PM
 *  Author: Mason
 */ 

#include <asf.h>
#include <math.h>
#include "thermistor.h"


void adc_init(void){	//This is for PA0
	PORTA.DIRCLR = 0b00000001;
	PORTA.DIR = 0b11111110;
	ADCA.CTRLA = 0b00000001;
	ADCA.CTRLB = 0b00000000;
	ADCA.REFCTRL = 0b00010000;
	ADCA.PRESCALER = 0b00000101;
	ADCA.CAL = adc_get_calibration_data(ADC_CAL_ADCA);
	
	ADCA.CH0.CTRL = 0b00000001;
	ADCA.CH0.MUXCTRL = 0b00000000;
}


float getVoltage(void){
	ADCA.CH0.CTRL  |= 0b10000000;
	//printf("one");
	while(ADCA.CH0.INTFLAGS == 0);
	//printf("two");
	ADCA.CH0.INTFLAGS = 0;
	//printf("three");
	uint16_t adcReading = ADCA.CH0.RES;
	//printf("ADC reading = %u\n", adcReading);
	float voltage = 0.0004899 * (float)(adcReading) - 0.0856326;	//We have to find these numbers by applying differing voltage, printing ADC readings, and solve equation
	//printf("voltage: %f \n", voltage);
	return voltage;
	
}
/*
uint16_t getCurrent(void){
	uint16_t voltage = getVoltage();
	uint16_t current = (voltage/10000);
	return current;
}
*/
float getTemperature(void){
	float voltage = getVoltage();
	//uint16_t current = getCurrent();
	//uint16_t resistance = voltage/current;
	float resistance = (voltage*10000)/(voltage-3.3);
	//printf("resistance = %f \n", resistance);
	float temperature = 3977.0/(log(resistance/(10000.0*pow(2.71828,(-3977.0/298.15)))));
	//float temperature = pow((.003351016+.0002569850*log(resistance/10000)+.000002620131*pow(log(resistance/10000),2)),-1);
	return temperature;
	
	
	
}