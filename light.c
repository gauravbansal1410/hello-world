// muRata FTN Starter Kit for RaspberryPi
// Last updated : 10-Aug.2016
//
//  ___Pin Layout of starter kit__
// |                              |
// |                      (5V)    |
// |____GND___OUT__________VCC____|
//
//
//
//
//
//
// Pin connection
// Starter Kit      ADC(MCP3208)      		            RaspberryPi 2
// VCC  <----->    pin16(VDD),pin15(VREF)   <----->      pin 2
// GND  <----->    pin14(AGND),pin9(DGND)   <----->		 pin 6
// COUT <----->    pin1(CH0)
//                 pin13(CLK)         	    <----->	     pin 23(SCLK)
//                 pin11(DIN)       	    <----->	     pin 19(MOSI)
//                 pin12(DOUT)       	    <----->	     pin 21(MISO)
//                 pin10(CS)      		    <----->	     pin 24(CE0)


#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const int PI_CE = 0;
const int CLK_SPEED = 320000;

double read_ADC3208(int pi_channel)
{
	unsigned char data[3] = {};
	int vcc = 5;
	int a_val;
	double vol;
	double temp;
	int adc_channel = 0;

	data[0] = 0b00000110 | (((adc_channel & 0x04)>>2));
	data[1] = 0b00000000 | (((adc_channel & 0x03)<<6));
	data[2] = 0;

	wiringPiSPIDataRW(pi_channel,data,sizeof(data));

	a_val = ((data[1]<<8)&0b111100000000) + (data[2]&0xff);
	//vol     = ((double)a_val/4095) * vcc;
	//temp    = -0.30779 * pow(vol,5) + 4.1545 * pow(vol,4) - 23.272 * pow(vol,3) +68.015 * pow(vol,2) -126.35*vol +160.42;
	temp=a_val;
	return temp;

}

int main(int arc, char **argv) 
{
	double g_cnt;
	char *logfile = "light.txt";
	FILE *fp;
	int i=1;

	printf( "\nStarter Kit : Light sensor\n");
	printf( "===============================================\n");

	if(wiringPiSPISetup(PI_CE,CLK_SPEED)<0){
		printf("SPI setup fail");
		return 1;
	}

	while(1){
		time_t timer = time(NULL);
		struct tm *local;
		local = localtime(&timer);
		int year = local->tm_year + 1900;
		int mon  = local->tm_mon + 1;
		int day  = local->tm_mday;
		int hour = local->tm_hour;
		int min  = local->tm_min;
		int sec  = local->tm_sec;
		g_cnt=read_ADC3208(PI_CE);
		fp = fopen(logfile, "a"); 
		fprintf(fp, "[%d]%4d/%2d/%2d %2d:%2d:%2d\t Lux : %.2lf\n", i, year, mon, day, hour, min, sec, g_cnt);
		fclose(fp);

		printf("[%d] %4d/%2d/%2d %2d:%2d:%2d\t Lux : %.2lf\n",i++, year, mon, day, hour, min, sec, g_cnt);
		
		sleep(1); 
	}
}
