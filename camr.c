// muRata AMR sensor Starter Kit for RaspberryPi
// Last updated : 12-Feb.2016
//
// _______Pin Layout of starter kit________
// | VCC                                   |
// | GND                                   |
// |_OUT___________________________________|
//
// Pin connection
// Starter Kit            RaspberryPi 2
// VCC            <-->    pin 1
// GND            <-->    pin 6
// OUT            <-->    pin 11 (GPIO0)

#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define COUT 0
#define LED  2

int  f_AMR;

void irq_handler(void){
	f_AMR = 1;
}

int main(void){
	int f_led = 0;
	int g_cnt = 0;
	char *logfile = "/home/pi/gaurav-bansal.github.io/log.txt";
	FILE *fp;

	fp = fopen(logfile, "a");
	fprintf(fp, "\nStarter Kit : AMR Sensor\n");
	fprintf(fp, "===============================================\n");
	fclose(fp);
	printf( "\nStarter Kit : AMR Sensor\n");
	printf( "===============================================\n");

	// GPIO initiallization	
	if(wiringPiSetup() == -1){
		fp = fopen(logfile, "a");
		fprintf(fp, "error wiringPi setup.\n");
		fclose(fp);
		printf("error wiringPi setup.\n");
		return 1;
	}
	pinMode(LED, OUTPUT);
	wiringPiISR(COUT, INT_EDGE_FALLING, irq_handler);

	while(1){
		if(f_AMR == 1){
			f_AMR = 0;
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

			fp = fopen(logfile, "a"); 
			fprintf(fp, "[%d]\t%4d/%2d/%2d %2d:%2d:%2d\tMagnet detected.\n", g_cnt, year, mon, day, hour, min, sec);
			fclose(fp);
			printf("[%d]\t%4d/%2d/%2d %2d:%2d:%2d\tMagnet detected.\n", g_cnt, year, mon, day, hour, min, sec);		


			if(f_led == 0){
				digitalWrite(LED, 1);
				f_led = 1;
			}else{
				digitalWrite(LED, 0);
				f_led = 0;
			}
		}
		delay(100);
	}

	return 0;
}

