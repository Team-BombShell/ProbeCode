/*
 * timer_counter.h
 *
 * Created: 9/7/2017 9:00:07 PM
 *  Author: Mason
 */ 
#include <asf.h>

#ifndef TIMER_COUNTER_H_
#define TIMER_COUNTER_H_


void timer_founter_init(uint16_t period, uint16_t duty_cycle);
//void timer_counter_setup(uint16_t period, uint16_t on, uint16_t off);
void timer_dounter_init(uint16_t period, uint16_t duty_cycle);
//void timer_dounter_setup(uint16_t period, uint16_t on, uint16_t off);
//void timer_eounter_init(void);
//void timer_eounter_setup(uint16_t period, uint16_t on, uint16_t off);



#endif /* TIMER_COUNTER_H_ */