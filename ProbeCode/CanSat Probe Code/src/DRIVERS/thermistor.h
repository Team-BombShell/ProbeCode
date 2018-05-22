/*
 * thermistor.h
 *
 * Created: 9/20/2017 9:26:46 PM
 *  Author: Mason
 */ 


#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include <asf.h>

void adc_init(void);
float getVoltage(void);
//uint16_t getCurrent(void);
float getTemperature(void);


#endif /* THERMISTOR_H_ */