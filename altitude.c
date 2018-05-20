#include <asf.h>
#include "altitude.h"
#include "pressure.h"
#include <math.h>

extern int32_t TEMP;

float Get_altitude(uint32_t initial, uint32_t pressure){
	printf("pressure = %lu \n", pressure);
	printf("temperature = %i \n", (uint16_t) TEMP);
	float altitude = (((287.058 * (((float)(TEMP)/100)+273.15)/9.8))*log((float)initial/get_pressure())*3.28);
	printf("altitude = %i \n", (int16_t)altitude);
	return altitude;
}

// uint32_t getAltitude(int32_t pressure, uint16_t* temperature){
// //uint32_t altitude = (((pow((initial_pressure/pressure),(1/5.257)))*(temperature))/.0065);
// //printf("temperature: %u \n", temperature);
// uint32_t altitude = (uint32_t)((287.058+(double)(*temperature))/9.81*log(101020.0/(double)(pressure)));
// // 	//printf("altitude: %u \n", altitude);
// // 	return altitude;
// // }
// 
// uint32_t getAltitude(int32_t P){
// 	uint32_t altitude = (uint32_t)(44330*(1-pow(((float)(P)/101020), (1/5.257))));
// 	return altitude;
// }

// uint32_t getInitial_altitude(uint32_t pressure, uint16_t temperature){
// 	uint32_t initial_altitude = getAltitude(pressure);
// 	return initial_altitude;
// }


// uint32_t getAverage_altitude(uint32_t pressure, uint16_t temperature){
// 	uint32_t average_altitude = getAltitude(pressure);	
// }
// 
// uint8_t getMy_time(void){
// 	uint8_t my_time = 0;
// 	return my_time;
// }

/*n = 0;
average_altitude = 0;
while n < 5{
	average_altitude = average_altitude + altitude;
	n = n + 1;
}
average_altitude/5;*/