// muRata Pressure sensor Starter Kit for RaspberryPi
// Last updated : 12-Feb.2016
//
// ___Pin Layout of starter kit__
// |                             |
// |                     (3.3V)  |
// |____GND___SDA___SCL___VCC____|
//
// Pin connection
// Starter Kit            RaspberryPi 2
// VCC            <-->    pin 1
// GND            <-->    pin 6
// SDA            <-->    pin 3
// SCL            <-->    pin 5

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define COUT 0
#define LED  2

// Device address is 0b101110x (=0x5c or 0x5d)
// LSB is decided by pull-up or pull-down of SA0 pin.
// Starter kit default is pull-down => 0b1011100 = 0x5c
#define DEVID		0x5c

// Device Register Address
#define CTRL_REG0	0x20
#define PRESS_OUT_XL	0x28
#define PRESS_OUT_L	0x29
#define PRESS_OUT_H	0x2a
#define TEMP_OUT_L	0x2b
#define TEMP_OUT_H	0x2c

int main(void){
	int g_cnt = 0;
	int f_led = 0;
	char *logfile = "pressurelog.txt";
	FILE *fp;

	//fp = fopen(logfile, "a");
	//fprintf(fp, "\nStarter Kit : Pressure Sensor\n");
	//fprintf(fp, "===============================================\n");
	//fclose(fp);

	printf("\nStarter Kit : Pressure Sensor\n");
	printf("===============================================\n");

	// GPIO initiallization	
	if(wiringPiSetup() == -1){
		fp = fopen(logfile, "a");
		fprintf(fp, "error wiringPi setup.\n");
		fclose(fp);
		printf("error wiringPi setup.\n");
		return 1;
	}
	pinMode(LED, OUTPUT);

	// I2C initiallization
	int fd;
	fd = wiringPiI2CSetup(DEVID);

	// Device Start 
	wiringPiI2CWriteReg8(fd, CTRL_REG0, 0x02);

	while(1){
		g_cnt++;

		time_t timer = time(NULL);
		struct tm *local;
		local = localtime(&timer);
		int year = local->tm_year + 1900;
		int mon  = local->tm_mon + 1;
		int day  = local->tm_mday;
		int hour = local->tm_hour;
		int min  = local->tm_min;
		int sec  = local->tm_sec;

		// Configure ONESHOT mode
		wiringPiI2CWriteReg8(fd, CTRL_REG0, 0x03);
		delay(170);	// Capacitance conversion time MAX = 166ms

		// Read Result
		int press_xl = wiringPiI2CReadReg8(fd, PRESS_OUT_XL);	// read pressure
		int press_l  = wiringPiI2CReadReg8(fd, PRESS_OUT_L);	// read pressure
		int press_h  = wiringPiI2CReadReg8(fd, PRESS_OUT_H);	// read pressure
		int temp_l   = wiringPiI2CReadReg8(fd, TEMP_OUT_L);	// read temperature
		int temp_h   = wiringPiI2CReadReg8(fd, TEMP_OUT_H);	// read temperature

		// Calculation
		long pres = (long)press_xl + (long)(press_l<<8) + (long)(press_h<<16);
		pres = pres >> 6;		// the least 6 bits are after the decimal point.		
		float temp = (float)temp_l + (float)(temp_h<<8);
		temp = temp * 0.00649 - 176.83;	// calculation is written in datasheet. 

		fp = fopen(logfile, "a"); 
		fprintf(fp, "[%d]\t%4d/%2d/%2d %2d:%2d:%2d\tPressure : %d (Pa)\tTemperature : %.1f (degC)\n", g_cnt, year, mon, day, hour, min, sec, pres, temp);
		fclose(fp);
		printf("[%d]\t%4d/%2d/%2d %2d:%2d:%2d\tPressure : %d (Pa)\tTemperature : %.1f (degC)\n", g_cnt, year, mon, day, hour, min, sec, pres, temp);

		if(f_led == 0){
			digitalWrite(LED, 1);
			f_led = 1;
		}else{
			digitalWrite(LED, 0);
			f_led = 0;
		}

		delay(2000);
	}

	return 0;
}

