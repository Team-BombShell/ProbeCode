/*
 * RTC.c
 *
 * Created: 6/4/2018 2:43:41 PM
 *  Author: amber
 */ 

#include <stdint.h>
#include "RTC.h"
#include <asf.h>
uint8_t writeData[RTC_PACKET_LENGTH];
uint8_t readData[RTC_PACKET_LENGTH};

twi_package_t write_packet = {
	.addr           =   0x00,
	.addr_length    =   sizeof(uint8_t),
	.chip           =   RTC_SLAVE_ADDR,
	.buffer         =   (void*)writeData,
	.length         =   sizeof(writeData)
};

twi_package_t read_packet = {
	.addr           =   0x00,
	.addr_length    =   sizeof(uint8_t),
	.chip           =   RTC_SLAVE_ADDR,
	.buffer         =   (void*)writeData,
	.length         =   sizeof(writeData)
};2.3
static inline uint8_t BCDtoDEC(uint8_t number)
{
	
	uint8_t temp = number & 0x0F;
	while(number>=0x10)
	{
		temp+= 10;
		number -= 0x10;
	}
	return temp;
}

static inline uint8_t DECtoBCD(uint8_t number)
{
	
	uint8_t temp = 0;
	while(number > 9)
	{
		
		temp += 0x10;
		number -=10;
	}
	return(temp+number);
}

void rtc_twi_init(){
	twi_master_options_t opt = {
		.speed = 500000,
		.chip = RTC_SLAVE_ADDR
	};
	twi_master_setup(&RTC_TWI, &opt);
	rtc_write_register(0x0E, 0x00);
}

void rtc_write_register(uint8_t regi,uint8_t val){
	write_packet.addr[0] = regi;
	write_packet.length = 1;
	writeData[0] = val;
	printf("Write data %u\n", writeData[0]);
	while(twi_master_write(&RTC_TWI, &write_packet) != TWI_SUCCESS);
}
uint8_t rtc_read_register(uint8_t regi){
	read_packet.addr[0] = regi;
	read_packet.length = 1;
	
	if (twi_master_read(&RTC_TWI, &read_packet) == TWI_SUCCESS);
	{
		return readData[0];
	}
	return 0;
}


void rtc_setTime(uint8_t seconds, uint8_t minutes, uint8_t hours){
	rtc_write_register(RTC_SECONDS, DECtoBCD(seconds)); 
	rtc_write_register(RTC_MINUTES, DECtoBCD(minutes));
	rtc_write_register(RTC_HOURS,DECtoBCD(hours));
}

uint8_t rtc_getSeconds(){
	return rtc_read_register(BCDtoDEC(RTC_SECONDS)); //So BCDtoDEC?
}

uint8_t rtc_getMinutes(){
	return rtc_read_register(BCDtoDEC(RTC_MINUTES));
}

uint8_t rtc_getHours(){
	return rtc_read_register(BCDtoDEC(RTC_HOURS));
}

uint32_t rtc_getTotalSeconds(){
	return 3600 * rtc_getHours() + 60 * rtc_getMinutes() + rtc_getSeconds();
} //Not sure how necessary this actually is