/*
 * RTC.c
 *
 * Created: 6/4/2018 2:43:41 PM
 *  Author: amber
 */ 

#include "RTC.h"
#include <asf.h>


//Taken from pressure.c, need to modify for RTC
void rtc_write(uint8_t data){
	SPIC.DATA = data;
	while(!(SPIC.STATUS>>7));
}

uint8_t rtc_read (void){
	SPI_write(0xFF);
	return SPIC.DATA;
}

//"Inspired" by Powerglide, need to make sure it's good to go

void rtc_setTime(uint8_t seconds, uint8_t minutes, uint8_t hours){
	rtc_write(RTC_SECONDS, DECtoBCD(seconds)); //So DECtoBCD?
	rtc_write(RTC_MINUTES, DECtoBCD(minutes));
	rtc_write(RTC_HOURS,DECtoBCD(hours));
}

uint8_t rtc_getSeconds(){
	return rtc_read(BCDtoDEC(RTC_SECONDS)); //So BCDtoDEC?
}

uint8_t rtc_getMinutes(){
	return rtc_read(BCDtoDEC(RTC_MINUTES));
}

uint8_t rtc_getHours(){
	return rtc_read(BCDtoDEC(RTC_HOURS));
}

uint32_t rtc_getTotalSeconds(){
	return 3600 * rtc_getHours() + 60 * rtc_getMinutes() + rtc_getSeconds();
} //Not sure how necessary this actually is