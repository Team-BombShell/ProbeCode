/*
 * RTC.h
 *
 * Created: 6/4/2018 2:44:00 PM
 *  Author: amber
 */ 


#ifndef RTC_H_
#define RTC_H_

void rtc_write(uint8_t data)
uint8_t rtc_read (void)
void rtc_setTime(uint8_t seconds, uint8_t minutes, uint8_t hours)
uint8_t rtc_getSeconds()
uint8_t rtc_getMinutes()
uint8_t rtc_getHours()
uint32_t rtc_getTotalSeconds()


#endif /* RTC_H_ */