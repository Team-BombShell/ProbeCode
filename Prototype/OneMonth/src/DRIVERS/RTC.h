/*
 * RTC.h
 *
 * Created: 6/4/2018 2:44:00 PM
 *  Author: amber
 */ 

#include <asf.h>
#ifndef RTC_H_
#define RTC_H_

#define RTC_PACKET_LENGTH 1

#define RTC_TWI     TWIC

#define RTC_SLAVE_ADDR 0xD0

#define RTC_SECONDS	0x00
#define RTC_MINUTES	0x01
#define RTC_HOURS	0x02
#define RTC_DAY		0x03
#define RTC_DATE	0x04
#define RTC_MONTH	0x05
#define RTC_YEAR	0x06	

void rtc_twi_init();
void rtc_write_register(uint8_t regi,uint8_t val);
uint8_t rtc_read_register(uint8_t regi);
void rtc_setTime(uint8_t seconds, uint8_t minutes, uint8_t hours)
uint8_t rtc_getSeconds(void)
uint8_t rtc_getMinutes(void)
uint8_t rtc_getHours(void)
uint32_t rtc_getTotalSeconds(void)


#endif /* RTC_H_ */