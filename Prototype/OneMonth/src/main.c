/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "Drivers/timer_counter.h"
#include "Drivers/usart_comms.h"
#include "Drivers/pressure.h"
#include "Drivers/thermistor.h"
#include "Drivers/altitude.h"
#include "DRIVERS/mpu9250.h"
#include "DRIVERS/mechanics.h"
#include "register_definitions.h"
#include <time.h>


extern uint8_t state;
//void blink (int, int);

int main (void)
{
	sysclk_init();
	sysclk_enable_peripheral_clock(&TCF0);
	sysclk_enable_peripheral_clock(&TCD0);
	sysclk_enable_module(SYSCLK_PORT_F, SYSCLK_HIRES);
	sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_HIRES);
	sysclk_enable_module(SYSCLK_PORT_C, PR_SPI_bm);
	
	
//	timer_founter_init(3124, 10);
	//PORTD.DIRSET = 0b00001000;
// 	PORTD.OUTSET = 0b00001000;
// 	timer_founter_init(3124, 0);
// 	delay_ms(15000);
// 	PORTD.OUTCLR = 0b00001000;
//	timer_founter_init(3124, 10);
		
		
	sysclk_enable_peripheral_clock(&USARTC0);
	usart_init();
	
	sysclk_enable_peripheral_clock(&SPIC);
	SPI_init();
	ms5607_init();
	
	sysclk_enable_peripheral_clock(&ADCA);
	adc_init();
	
	//GPS initializations
	init_GPS_pins_and_usart();
	init_gps_buffers();
	init_gps_interrupts();
	
	uint16_t teamID = 5186;
	uint8_t my_time = 0;
	uint8_t packetCount;
	float voltage;
	uint32_t GPSTime;
	uint32_t GPSLat;
	uint32_t GPSLong;
	uint32_t GPSAlt;
	uint32_t GPSSats;
	float tiltX;
	float tiltY;	
	float tiltZ;	
	
	//printf("Is this thing on?\n");
	uint32_t initial = get_pressure();
	uint32_t pressure;
	uint32_t temperature;
	uint32_t initial_pressure = get_pressure();
	int32_t altitude;
	int32_t initial_altitude = 0;
	int32_t smooth_altitude = 0;
	
	uint16_t period;
	uint16_t duty_cycle;
	double smoothing_factor = 0.90;
	

	uint8_t state = 0;
	
	//initial_altitude = Get_altitude(101300, initial);
	//timer_founter_init(62499, 5);

	//timer_dounter_init(12500, 10);
	
	
	
	
	while(1){
		sprintf("Hello World! \n"," ");
		pressure = get_pressure();
		temperature = getTemperature();
		//printf("Pressure = %lu\n", pressure);
		//temperature = (temperature/100)+273;
		//printf("initial pressure: %lu \n", initial_pressure);
		altitude = Get_altitude(initial, pressure, temperature);
		smooth_altitude = (int32_t)(smoothing_factor * altitude + (1-smoothing_factor)*smooth_altitude);
		my_time = my_time + 1;
		//timer_founter_init(6249, 10);
		//printf("Temperature = %u \n", temperature);
		//printf("Pressure = %lu ~\n", pressure);
		//printf("Altitude = %li \n", (int32_t)altitude);
		const char data[256] = {(char)teamID,(char)teamID};
		printf(data);		
		
		delay_ms(1000);

		//const char* data = (const char)teamID +  (const char)my_time+ (const char*)packetCount+ (const char*)altitude+ (const char*)pressure+ 
		//(const char)temperature+ (const char*)voltage+ (const char*)GPSTime+ (const char*)GPSLat+ (const char*)GPSLong+ (const char*)GPSAlt+ (const char*)GPSSats+
		//	(const char*)tiltX+(const char*)tiltY+(const char*)tiltZ+(const char*)state;
		
		
		//float* data = pressure;
		//char data = printf("Team ID: %u ~\nMy Time: %u ~\nPacket Count: %u ~\nAltitude: %lu ~\nPressure: %lu ~\nTemperature: %lu ~\nVoltage: %f ~\nGPS Time: %lu ~\nGPS Lat: %lu ~\nGPS Long: %lu ~\nGPS Alt: %lu ~\nGPS Sats: %lu ~\nTilt X: %f ~\nTilt Y: %f ~\nTilt Z: %f ~\nState: %u ~\n\n", teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats, tiltX, tiltY, tiltZ, state);	
		//char sd_data = sprintf("Team ID: %u ~\nMy Time: %u ~\nPacket Count: %u ~\nAltitude: %lu ~\nPressure: %lu ~\nTemperature: %lu ~\nVoltage: %f ~\nGPS Time: %lu ~\nGPS Lat: %lu ~\nGPS Long: %lu ~\nGPS Alt: %lu ~\nGPS Sats: %lu ~\nTilt X: %f ~\nTilt Y: %f ~\nTilt Z: %f ~\nState: %u ~\n\n", teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats, tiltX, tiltY, tiltZ, state);	("Team ID: %u\nMy Time: %u\nPacket Count: %u\nAltitude: %lu\nPressure: %lu\nTemperature: %lu\nVoltage: %f\nGPS Time: %lu\nGPS Lat: %lu\nGPS Long: %lu\nGPS Alt: %lu\nGPS Sats: %lu\nTilt X: %f\nTilt Y: %f\nTilt Z: %f\nState: %u\n\n", teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats, tiltX, tiltY, tiltZ, state);	
		//usart_tx(&USARTC0, &data);
		
		
	
	
	// Flight States!
	
		//FS0
		if(state==0){
			//printf("Flight State 0 \n");
			PORTE.DIRSET = 0b01010101;
			PORTE.OUTSET = 0b01010101;
			
			PORTA.OUT = 0b00001000; //Hopefully this does the buzzer... buzzer is really quiet rn, gotta fix that. (this is just for testing)
			if(smooth_altitude-altitude<0 && 600<smooth_altitude && smooth_altitude<800){ //Work on Velocity later, this will work for now
				PORTE.DIRSET = 0b00000001;	//Deploy Heat Shield
				PORTE.OUTSET = 0b00000001;	//Deploy Heat Shield
				state = 1;
			}
		}
		
		//FS1
		if(state==1){
			//printf("Flight State 1 \n");
			if(smooth_altitude-initial_altitude<300){
				PORTE.DIRSET = 0b00000010;	//Activate Camera
				PORTE.OUTSET = 0b00000010;	//Activate Camera
				PORTA.DIRSET = 0b10000000;	//Detach Heat Shield
				PORTA.OUTSET = 0b10000000;	//Detach Heat Shield
				//Deploy Parachute
				state = 2;
			}
		}
		
		//FS2
		if(state==2){
			//printf("Flight State 2 \n");
			if(smooth_altitude-altitude<1 && altitude-initial_altitude<100){
				PORTA.DIRSET = 0b00001000; //Activate Buzzer
				PORTA.OUTSET = 0b00001000; //Activate Buzzer
				state = 3;
			}
		}
	
	
	
	
	}
	
	//Old Flight States
	
	/*
	
	// Flight State 0 - 1
		if (state == 0){
			printf("Flight state 0 \n");
			//printf("stage 1 transfer: %lu \n", smooth_altitude-altitude);
			if (altitude-initial_altitude>30){
				state = 1;
				timer_founter_init(6249, 10);
				printf("Flight state 1 \n");
			}
	
		}
		// Flight State 1 - 2 
		if (state == 1){
			if (altitude-initial_altitude>700){
				state = 2;
				timer_founter_init(3124, 0);
				PORTD.DIRSET = 0b00001000;
				PORTD.OUTSET = 0b00001000;
				//timer_founter_init(3124, 0);
				delay_ms(15000);
				PORTD.OUTCLR = 0b00001000;
				timer_founter_init(3124, 10);
				printf("Flight State 2 \n");
				}
				//^^^Hot wire
			
			
			}
		
		// Flight State 2 - 3
		if(state == 2){
			if(abs(smooth_altitude-altitude<10) && altitude-initial_altitude<100){
				state = 3;
				timer_founter_init(31250, 10);
				//timer_dounter_init(1250, 10);
				printf("Flight Stage 3 \n");
			}
		}
		
		
		
		if(state == 3){
			while(1);
		}
		
	}
		printf("Temperature = %u\n", temperature);
		printf("Pressure = %"PRIu32"\n", pressure);
		printf("Pressure = %lu\n", pressure);
		
		
	}


	
	//blink(500, 1000);
	//blink(500, 1000);
	
	while (1==1)
	{
		PORTE.OUT = 0b01010101;
		delay_ms(100);
		PORTE.OUT = 0b10101010;
		delay_ms(100);
	}

	while (1==1){
		PORTE.OUT = 0b01111111;
		delay_ms(250);
		PORTE.OUT = 0b10111111;
		delay_ms(250);
		PORTE.OUT = 0b11011111;
		delay_ms(250);
		PORTE.OUT = 0b11101111;
		delay_ms(250);
		PORTE.OUT = 0b11111110;
		delay_ms(250);
		PORTE.OUT = 0b11111101;
		delay_ms(250);
		PORTE.OUT = 0b11111011;
		delay_ms(250);
		PORTE.OUT = 0b11110111;
		delay_ms(250);
	}


void blink (int, int);

void blink (int time_on, int time_off){
	PORTE.OUT - 0b00000000;
	delay_ms(time_on);
	PORTE.OUT = 0b11111111;
	delay_ms(time_off);
}*/


}




//I stole this from Thomas it does cool GPS things

	if (last_finished != SENTENCE_NONE)
	{
		if (last_finished == SENTENCE_GPGGA)
		{
			//printf("GGA!!!\n");
			ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
			{
				memcpy(gpstmp, gpgga_buff, 85);
			}
			// 				uint8_t* gpsstr = "$GPGGA,052430.779,3443.3629,N,08638.2812,W,1,05,1.74,188.1,M,-30.4,M,,*58";
			// 				strcpy(gpstmp, gpsstr);
			gpstmp[packetlen(gpstmp)] = '\0';
			//printf(gpstmp);
			//putchar('\n');
			
			//usart_serial_write_packet(&XBEE_USART, gpstmp, 85);
			tempgpsdata = getGPSDatafromNMEA(gpstmp, strlen(gpstmp));
			//printf("test");
			//printf("%c",tempgpsdata->hour[0]);
			//printf("test2\n");
			//if (strlen(tempgpsdata->altitude) > 1)
			//	printf("Altitude: %s\n", tempgpsdata->altitude);
			
			//printf("no of sats: %s\n", tempgpsdata->noofsatellites);
			//printf("Altitude: %u, minutes: %u, valid: %u\n", (uint16_t)tempgpsdata->altitude, tempgpsdata->minutes, tempgpsdata->fix_status ? 1 : 0);
			//GPSdata->altitude = tempgpsdata->altitude;
			GPSdata = tempgpsdata;
			//memcpy(GPSdata->noofsatellites, tempgpsdata->noofsatellites, 3);
			last_finished = SENTENCE_NONE;
			
			if (GPSdata.fix_status)
			{
				uint32_t GPS_secs = 3600 * (uint32_t)GPSdata.hour + 60 * (uint32_t)GPSdata.minutes + (uint32_t)GPSdata.seconds;
				uint32_t safetime;
				ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
				{
					safetime = time_ms;
				}
				gps_local_delta = GPS_secs - safetime;
				got_good_time = 1;
			}
			// 				uint16_t delta;
			// 				ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
			// 				{
			// 					delta = time_ms - begin_parse;
			// 				}
			// 				printf("Difference is %u\n", delta);
		}
	}
}
}
