/*
 * pressure.h
 *
 * Created: 9/20/2017 8:48:12 PM
 *  Author: Mason
 */ 


#ifndef PRESSURE_H_
#define PRESSURE_H_

#include <asf.h>

void SPI_init(void);
void SPI_write(uint8_t data);
uint8_t spi_read (void);
void ms5607_init(void);
uint16_t prom_read(uint8_t command);
uint32_t data_read(uint8_t command);
uint32_t get_pressure(void);
int32_t TEMP;

#endif /* PRESSURE_H_ */