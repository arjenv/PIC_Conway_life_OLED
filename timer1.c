/*************************************

	timer1.c
	Routines to initialise timer1
		set an output to blink a LED
		set interrupt routine

	ARV 23 november 2025

***************************************/

#include "timer1.h"


void init_Timer1(void) {
	//TRISB0 = 0; // Only when you want LED blink
	//RB0 = 0;
	T1CKPS1 = 1;
	T1CKPS0 = 1; // prescaler to /8
 
	T1OSCEN = 0; 
	TMR1CS = 0; // Fosc/4
	// Set following 3 registers to 1 for LED blink
	GIE = 0;   // global interrupt
	PEIE = 0;  
	TMR1IE = 0; // tmr1 interrupt
	TMR1ON = 1; // enabling timer
}


/* // Interrupt routine to blink LED
interrupt isr() {
 
	if (TMR1IF) {
		//count++;
		RB0 = !RB0;
		TMR1IF = 0;  
	}
}
*/