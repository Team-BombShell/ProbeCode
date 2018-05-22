/*
 * altitude.h
 *
 * Created: 9/23/2017 11:12:04 PM
 *  Author: Mason
 */ 


#ifndef ALTITUDE_H_
#define ALTITUDE_H_

//uint32_t getInitial_pressure(void);
//uint32_t getAltitude(int32_t pressure);
float Get_altitude(uint32_t initial, uint32_t pressure);
uint32_t getInitial_altitude(uint32_t pressure, uint16_t temperature);
//uint32_t getAverage_altitude(uint32_t pressure, uint16_t temperature);
uint8_t getMy_time(void);



#endif /* ALTITUDE_H_ */