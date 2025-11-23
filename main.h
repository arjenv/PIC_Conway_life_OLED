/************************************************
*
*	PIC16F628A to OLED
*	Example functions include file for OLED SSD1306
*	ARV november 2025
*
************************************************/


#ifndef OLEDLIB_H
#define OLEDLIB_H

//#define RS232
#include <htc.h>
//#include <stdlib.h>
//#include <stdio.h>

#include "oledlib.h"
#if defined RS232
	#include "rs232.h"
#endif
#include "life_bit.h"
#include "timer1.h"

#define SSD1306_I2C_ADDRESS   0x78
#define SSD1306_SWITCHCAPVCC  0x02 // this is the default

#define _XTAL_FREQ 20000000
// #define _XTAL_FREQ 4000000 // when you chose the internal oscillator

__CONFIG (WDTE_OFF & FOSC_HS & PWRTE_OFF & CP_OFF & BOREN_OFF & MCLRE_ON & LVP_OFF & CPD_OFF);
//__CONFIG (WDTE_OFF & FOSC_INTOSCIO & PWRTE_OFF & CP_OFF & BOREN_OFF & MCLRE_ON & LVP_OFF & CPD_OFF);

#endif   
