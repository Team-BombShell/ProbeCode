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
#include <string.h>
#include <time.h>
#include <util/atomic.h>
#include "Drivers/timer_counter.h"
#include "Drivers/usart_comms.h"
#include "Drivers/pressure.h"
#include "Drivers/thermistor.h"
#include "Drivers/altitude.h"
#include "DRIVERS/mpu9250.h"
#include "DRIVERS/mechanics.h"
#include "register_definitions.h"
#include "DRIVERS/GPS.h"
#include "DRIVERS/GPS_Interrupts.h"
#include "drivers/imu.h"




extern uint8_t state;
//void blink (int, int);
uint16_t packetlen(const uint8_t* buff);
uint16_t packetlen(const uint8_t* buff)
{
	uint16_t i = 0;
	for (i = 0; i < 1024; i++)
	{
		if (buff[i] == '\n')
		return i;
	}
	return 1024;
}

int main (void)
{
	
	sysclk_init();
	//sysclk_enable_peripheral_clock(&TCF0);
	sysclk_enable_peripheral_clock(&TCD0);


	sysclk_enable_module(SYSCLK_PORT_C, PR_SPI_bm);
	sysclk_enable_module(SYSCLK_PORT_C,SYSCLK_HIRES);
	sysclk_enable_module(SYSCLK_PORT_D, SYSCLK_HIRES);
	sysclk_enable_module(SYSCLK_PORT_E,SYSCLK_HIRES);	
	sysclk_enable_module(SYSCLK_PORT_F, SYSCLK_HIRES);
	
	
//	timer_founter_init(3124, 10);
	//PORTD.DIRSET = 0b00001000;
// 	PORTD.OUTSET = 0b00001000;
// 	timer_founter_init(3124, 0);
// 	delay_ms(15000);
// 	PORTD.OUTCLR = 0b00001000;
//	timer_founter_init(3124, 10);
	sysclk_enable_peripheral_clock(&TCE0);
	sysclk_enable_peripheral_clock(&TCC0);
	//timer_counter_init(6249, 10);
	//heatshield_servo();
		
	sysclk_enable_peripheral_clock(&USARTC0);
	sysclk_enable_peripheral_clock(&USARTD1);
	usart_init();
	
	sysclk_enable_peripheral_clock(&SPIC);
	spi_init();
	ms5607init();
	
	sysclk_enable_peripheral_clock(&ADCA);
	adc_init();
	
	twi_options_t m_options = {
		.speed = 400000,
		.speed_reg = TWI_BAUD(32000000, 400000),
	};
	
	sysclk_enable_peripheral_clock(&TWIC);
	twi_master_init(&TWIC, &m_options);
	twi_master_enable(&TWIC);
	init_imu();
	
	
	
	//printf("Do you work?\n");
	//printf("Hi");

	
	uint8_t gpstmp[85];
	GPS_data_t gps_data;
	uint8_t got_good_time = 0;
	int32_t gps_local_delta; //local time + this = gps time (ish)
	
	uint32_t time_ms;
	uint32_t cycles = 0;
	
	
	uint16_t teamID = 5186;
	uint32_t my_time = 0;
	uint16_t packetCount;
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
	
	//printf((const char*)gps_data.latdegrees);
	PressData pdi = get_pressure();
	int32_t initial = pdi.P;
	uint32_t pressure;
	uint32_t temperature;
	//uint32_t initial_pressure = get_pressure();
	int32_t altitude;
	int32_t initial_altitude = 0;
	int32_t smooth_altitude = 0;
	int32_t max_altitude = 0;
	float smooth_x;
	float smooth_y;
	float smooth_z;
	
	//uint16_t period;
	//uint16_t duty_cycle;
	double smoothing_factor = 0.50;
	

	uint8_t state = 0;
	//printf("Is this thing on?\n");

	//initial_altitude = Get_altitude(101300, initial);
	//timer_founter_init(62499, 5);

	//timer_dounter_init(12500, 10);
	init_GPS_pins_and_usart();
	init_gps_interrupts();
	init_gps_buffers();
	
	//timer_counter_init(6249,10);
	//TCD0.INTCTRLA = 0b00000001;
	
// 	PORTD_DIRSET = 0b00100000;
// 	PORTD_OUTCLR = 0b00100000;
// 	delay_ms(100);
// 	PORTD_OUTSET = 0b00100000;
// 	delay_ms(1);
// 	PORTD_OUTCLR = 0b00100000;
	//delay_ms(5000);
	//printf("Hello World! \n");

	buzzer_on();
	TCC0.INTCTRLA = 0b00000001;
	
	pmic_init();
	pmic_set_scheduling(PMIC_SCH_FIXED_PRIORITY);
	cpu_irq_enable();
	
	
	//while(1){
		//PORTB.OUTTGL = 0b00000001;
		//delay_ms(1);
	//}
	while(1){
		//printf("IT'S TIME TO STOP!!!! \n");
// 		buzzer_on();
//  	PORTA_DIR = 0b00011110;
//  	PORTA_OUT = 0b00011110;
//  	delay_ms(250);
//  	PORTA_OUT = 0b00000000;
//  	delay_ms(250);
		
		PressData pd = get_pressure();
		pressure = pd.P;
		TEMP = pd.TEMP;
// 		pressure = get_pressure();
// 		temperature = getTemperature();
		//printf("Pressure = %lu\n", pressure);
		//temperature = (temperature/100)+273;
		//printf("initial pressure: %lu \n", initial_pressure);
		altitude = Get_altitude(initial, pressure);
		smooth_altitude = (int32_t)(smoothing_factor * altitude + (1-smoothing_factor)*smooth_altitude);
		my_time = my_time + 1;
	
		if (last_finished != SENTENCE_NONE)
		{
			//printf("Is it you?");
			if (last_finished == SENTENCE_GPGGA)
			{
				//printf("GGA!!!\n");
				
				ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
				{
					memcpy(gpstmp, gpgga_buff, 85);
				}
				gpstmp[packetlen(gpstmp)] = '\0';
				//printf(gpstmp);
				GPS_data_t gps_data = getGPSDatafromNMEA(gpstmp, strlen(gpstmp));
				GPSAlt =	gps_data.altitude;
				GPSLat =	gps_data.latdecimal;
				GPSLong=	gps_data.londecimal;
				
				last_finished = SENTENCE_NONE;
				
				if (gps_data.fix_status)
				{
					uint32_t GPS_secs = 3600 * (uint32_t)gps_data.hour + 60 * (uint32_t)gps_data.minutes + (uint32_t)gps_data.seconds;
					uint32_t safetime;
					ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
					{
						safetime = time_ms;
					}
					gps_local_delta = GPS_secs - safetime;
					got_good_time = 1;
				}
				
			}
		}
		//timer_founter_init(6249, 10);
		//printf("Temperature = %u \n", temperature);
		//printf("Pressure = %lu ~\n", pressure);
		//printf("Altitude = %li \n", (int32_t)altitude);
		
		imu_data_t imudata = imu_update(cycles);
		tiltX = imudata.pitch;
		tiltY = imudata.roll;
		tiltZ = imudata.yaw;
		
		smooth_x = (smoothing_factor * tiltX + (1.0-smoothing_factor)*smooth_x);
		smooth_y = (smoothing_factor * tiltY + (1.0-smoothing_factor)*smooth_y);
		smooth_z = (smoothing_factor * tiltZ + (1.0-smoothing_factor)*smooth_z);
		//X -21 Y 4.4    Z -11.5
		//delay_ms(500);
		
		PORTA_DIR = 0b00011110;
		PORTA_OUT = 0b00011110;
		delay_ms(250);
		PORTA_OUT = 0b00000000;
		delay_ms(250);
		
		/*float data[16] = {teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats,
			tiltX,tiltY,tiltZ,state};*/
		//temperature = 42;
		//NEED TO MOVE FLIGHT STATE BACK TO THE END OF THIS LINE
		printf("$%u,%"PRIu32",%u,%"PRIi32",%"PRIi32",%"PRIi32",%f,%"PRIi32",%"PRIi32",%"PRIi32",%"PRIi32",%"PRIi32",%f,%f,%f,%u\n",teamID,my_time,packetCount,altitude,pressure,(TEMP + 50) / 100,voltage,GPSTime,GPSLat,GPSLong,GPSAlt,GPSSats,smooth_x,smooth_y,smooth_z,state);
		packetCount++;
		//float* data = pressure;
		//char data = printf("Team ID: %u ~\nMy Time: %u ~\nPacket Count: %u ~\nAltitude: %lu ~\nPressure: %lu ~\nTemperature: %lu ~\nVoltage: %f ~\nGPS Time: %lu ~\nGPS Lat: %lu ~\nGPS Long: %lu ~\nGPS Alt: %lu ~\nGPS Sats: %lu ~\nTilt X: %f ~\nTilt Y: %f ~\nTilt Z: %f ~\nState: %u ~\n\n", teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats, tiltX, tiltY, tiltZ, state);	
		//char sd_data = sprintf("Team ID: %u ~\nMy Time: %u ~\nPacket Count: %u ~\nAltitude: %lu ~\nPressure: %lu ~\nTemperature: %lu ~\nVoltage: %f ~\nGPS Time: %lu ~\nGPS Lat: %lu ~\nGPS Long: %lu ~\nGPS Alt: %lu ~\nGPS Sats: %lu ~\nTilt X: %f ~\nTilt Y: %f ~\nTilt Z: %f ~\nState: %u ~\n\n", teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats, tiltX, tiltY, tiltZ, state);	("Team ID: %u\nMy Time: %u\nPacket Count: %u\nAltitude: %lu\nPressure: %lu\nTemperature: %lu\nVoltage: %f\nGPS Time: %lu\nGPS Lat: %lu\nGPS Long: %lu\nGPS Alt: %lu\nGPS Sats: %lu\nTilt X: %f\nTilt Y: %f\nTilt Z: %f\nState: %u\n\n", teamID, my_time, packetCount, altitude, pressure, temperature, voltage, GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats, tiltX, tiltY, tiltZ, state);	
		//usart_tx(&USARTC0, &data);
		
		//char gps = printf("Time: %lu\nLat: %lu\nLong: %lu\nAlt: %lu\nSats: %lu\n\n", GPSTime, GPSLat, GPSLong, GPSAlt, GPSSats);
		//char tilt = printf("X: %f\nY: %f\nZ: %f\n\n", tiltX, tiltY, tiltZ);
		
		
	
	
	// Flight States!
	
		//FS0
		if(state==0){
			//printf("Flight State 0 \n");
			//PORTE.DIRSET = 0b01010101;
			//PORTE.OUTSET = 0b01010101;
			
			servo_counter(.75);
			//PORTA.OUT = 0b00001000; //Hopefully this does the buzzer... buzzer is really quiet rn, gotta fix that. (this is just for testing)
			//printf("max alt: %"PRIi32"\n", max_altitude);
			if ((int32_t)max_altitude - (int32_t)altitude > 50){ //Work on Velocity later, this will work for now
				PORTE.DIRSET = 0b00000001;	//Deploy Heat Shield
				PORTE.OUTSET = 0b00000001;	//Deploy Heat Shield
				state = 1;
			}
			if(altitude > max_altitude) {
				max_altitude = altitude;
			}
		}
		
		//FS1
		if(state==1){
			//printf("Flight State 1 \n");
			if(altitude-initial_altitude<300){
				//PORTE.DIRSET = 0b00000010;	//Activate Camera
				//PORTE.OUTSET = 0b00000010;	//Activate Camera
				PORTA.DIRSET = 0b10000000;	//Detach Heat Shield and deploy parachute
				PORTA.OUTSET = 0b10000000;	//Detach Heat Shield and deploy parachute
				state = 2;
			}
		}
		
		//FS2
		if(state==2){
			//printf("Flight State 2 \n");
			if(smooth_altitude-altitude<3 && altitude-initial_altitude<50){
				buzzer_counter_init(104, 50);
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


