/**************************
*
*	include file for I2C routines
*
*	Change the SDA and SCL ports to your port
*	Change SDA_DIR and SCL_DIR accordingly
*
*	ARV november 2025
*
*****************************/


#ifndef I2C_SOFT_H
#define I2C_SOFT_H

#include <htc.h>

#define FAST_I2C // Speed things up but not according to spec..

#define SDA RB7 //pin2
#define SCL RB6 //pin1
#define SDA_DIR TRISB7 //SDA i/o direction
#define SCL_DIR TRISB6 // SCL i/o direction 

#ifndef _XTAL_FREQ
	#define _XTAL_FREQ 20000000 // was 400000
#endif

void I2C_startBit(void);
void I2C_sendData(unsigned char dataB);
void I2C_stopBit(void);
void I2C_clock(void);
void init_I2C();

#endif   
