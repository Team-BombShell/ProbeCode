/*
 * pressure.c
 *
 * Created: 9/20/2017 8:03:10 PM
 *  Author: Mason
 */ 
#include "Drivers/pressure.h"
#include <asf.h>

uint16_t c1;
uint16_t c2;
uint16_t c3;
uint16_t c4;
uint16_t c5;
uint16_t c6;


void SPI_init(void){
	PORTC.DIRSET = 0b10110000;
	PORTC.DIRCLR = 0b01000000;
	PORTC.OUTSET = 0b10110000;
	SPIC.CTRL = 0b01010011;
}

void SPI_write(uint8_t data){
	SPIC.DATA = data;
	while(!(SPIC.STATUS>>7));
}

uint8_t spi_read (void){
	SPI_write(0xFF);
	return SPIC.DATA;
}

void ms5607_init(void){
	PORTC.OUTCLR = 0b00010000;
	SPI_write(0x1E);
	PORTC.OUTSET = 0b00010000;
	delay_ms(10);
	c1 = prom_read(0xA2);
	//printf("c1: %u \n", c1);
	c2 = prom_read(0xA4);
	//printf("c2: %u \n", c2);
	c3 = prom_read(0xA6);
	//printf("c3: %u \n", c3);
	c4 = prom_read(0xA8);
	//printf("c4: %u \n", c4);
	c5 = prom_read(0xAA);
	//printf("c5: %u \n", c5);
	c6 = prom_read(0xAC);
	//printf("c6: %u \n", c6);
}

uint16_t prom_read(uint8_t command){
	uint16_t data;
	PORTC.OUTCLR = 0b00010000;
	SPI_write(command);
	data = ((uint16_t)spi_read())<<8;	//Bitshifting
	data += spi_read();
	PORTC.OUTSET = 0b00010000;
	delay_ms(1);
	//printf("data: %lu \n", data);
	return data;
}

uint32_t data_read(uint8_t command){
	uint32_t data;
	PORTC.OUTCLR = 0b00010000;
	SPI_write(command);
	PORTC.OUTSET = 0b00010000;
	delay_ms(9);
	PORTC.OUTCLR = 0b00010000;
	SPI_write(0x00);
	data = ((uint32_t)spi_read())<<16;
	data += ((uint32_t)spi_read())<<8;
	data += spi_read();
	PORTC.OUTSET = 0b00010000;
	return data;
}

uint32_t get_pressure(void){
	uint32_t D1 = data_read(0x48);
	//printf("D1: %lu \n", D1);
	uint32_t D2 = data_read(0x58);
	//printf("D2: %li \n", D2);
	int32_t dT = (int64_t)D2 - (int64_t)c5 * 256;
	TEMP = (int16_t)((int64_t)2000 + (int64_t)dT * (int64_t)c6 / (int64_t)(8388608));
	int64_t OFF = (int64_t)c2 * 131072 + (int64_t)(c4 * dT) / 64;
	int64_t SENS = (int64_t)c1 * 65536 + (int64_t)(c3 * dT) / 128;
	int32_t P = (int32_t)(((int64_t)((int64_t)(D1) * SENS) / 2097152 - (int64_t)OFF) / 32768);
	//printf("pressure: %lu \n", P);
	return (uint32_t)P;
}
	
	/*
	int x = 3;
	doubleme(&x);
	printf("%i\n", x);
	
	x * 2;
	&x;
	
	int* y;
	y = &x;
	
}

void doubleme(int* x)
{
	*x = *x * 2;
}*/
