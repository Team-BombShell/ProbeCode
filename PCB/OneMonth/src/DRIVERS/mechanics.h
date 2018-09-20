/*
 * mechanics.h
 *
 * Created: 5/31/2018 6:22:24 PM
 *  Author: Mason
 */ 


#ifndef MECHANICS_H_
#define MECHANICS_H_
#include <asf.h>

void heatshield_servo(void);
void heatshield_solenoid(void);
void heatshield_hotwire (void);
void heatshield_detatch_hotwire(void);
void parachute_hotwire(void);
void buzzer_on(void);
void buzzer_off(void);
void camera_on(void);
void camera_off(void);

#endif /* MECHANICS_H_ */