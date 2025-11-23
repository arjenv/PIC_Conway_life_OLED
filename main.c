/**************************************************************************************

LIFE! (Conway)
PIC16F628A to OLED
Example function for OLED SSD1306
ARV 23 november 2025
V1.0


***************************************************************************************/

#include "main.h"

void main() {

	unsigned int i;
	CMCON = 0b111;		//comparator off

	init_I2C(); // set ports for I2C
	Oled_Init(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	init_Timer1(); // timer1 used for random number generator

	Oled_ClearDisplay(0);
  	Oled_GotoXY(1, 2);
  	Oled_Print("Conway's LIFE!\n\n");
  	Oled_Print("V1.0 23 nov 2025\n\n by ARV");
  __delay_ms(5000);

	initGrid_pattern1();
	Oled_ClearDisplay(0);
	Oled_GotoXY(6,4);
	Oled_Print("Pattern 1..");
  __delay_ms(5000);

    for (i = 0; i < ITERATION; i++) {
        printGrid();
        updateGrid();
    }

	while(1) {
		Oled_ClearDisplay(0);
		Oled_GotoXY(6,4);
		Oled_Print("Random..");
	  __delay_ms(5000);
		initGrid(1);
		for (i=0; i<ITERATION; i++) {
			printGrid();
			updateGrid();
		}
	}
}

// End



