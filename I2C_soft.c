/**********************************
*
*	I2C (software) routines
*
*	ARV November 2025
*
*	Added #define FAST_I2C
*		to speed things up
*		but outside I2C standard
*		(seems to work though)
*
**********************************/



#include <htc.h>
#include "I2C_soft.h"

void I2C_startBit(void)
{
    SDA=0;
    __delay_us(5);
    SCL=0;

}

#if defined FAST_I2C 
	void I2C_sendData(unsigned char dataB) {
    	for(unsigned char b=0;b<8;b++){
       		SDA=(dataB >> (7-b)) & 0x01;
	       	SCL=1;
			SCL=0;
	    }	
    	//SDA_DIR=1;   //SDA input
	    SCL=1;
		SCL=0;
	    //__delay_us(1); // default 5
    	//SDA_DIR=0;   //SDA output

	}

	void I2C_clock(void) {
   		//__delay_us(1);
   		SCL=1;
   		//__delay_us(CLOCK_DELAY);
   		SCL=0;
   		//__delay_us(1);
	}

#else
	void I2C_sendData(unsigned char dataB) {
    	for(unsigned char b=0;b<8;b++){
	       SDA=(dataB >> (7-b)) % 2;
    	   I2C_clock();
	    }
    	SDA_DIR=1;   //SDA input
	    I2C_clock();
  	  __delay_us(5); // default 5
    	SDA_DIR=0;   //SDA output
	}

	void I2C_clock(void) {
  	__delay_us(1);
   		SCL=1;
  	__delay_us(5);
   		SCL=0;
  	__delay_us(1);
	}
#endif



void I2C_stopBit(void)
{
    SCL=1;
    __delay_us(5);
    SDA=1;

}

void init_I2C() {
	SDA_DIR = 0; // set to output
	SCL_DIR = 0;
    SCL=1;	
    SDA=1;
}