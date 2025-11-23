/******************************************************************************
 SSD1306 OLED driver for MPLAB PIC controller                                 *
 Software I2C driver                                                          *
 The driver is for I2C mode only.                                             *
                    														  *
 ARV nov 2025																  *
																			  *
 With thanks to:															  *
	 https://simple-circuit.com/mikroc-ssd1306-oled-pic-microcontroller/      *
	 Adafruit library for the SSD1306										  *
 																			  *
*******************************************************************************/

#include "oledlib.h"

void Oled_command(uint8_t c) {
    I2C_startBit();
    I2C_sendData(SSD1306_I2C_ADDRESS);
    I2C_sendData(0x00);
    I2C_sendData(c);
    I2C_stopBit();
}

void Oled_Init(uint8_t vccstate, uint8_t i2caddr) {
	#ifdef SSD1306_RST
    	SSD1306_RST = 0;
    	#ifdef SSD1306_RST_DIR
      		SSD1306_RST_DIR = 0;
    	#endif
    	delay_ms(10);
    	SSD1306_RST = 1;
  	#endif
  	// Init sequence
	// Some commands are commented out since they appear to be default

  	Oled_command(SSD1306_DISPLAYOFF);                    // 0xAE
  	//Oled_command(Oled_SETDISPLAYCLOCKDIV);            // 0xD5 <this is set by default>
  	//Oled_command(0x80);                                  // the suggested ratio 0x80

  	#if !defined SSD1306_128_64								// <default = 64-1)
		Oled_command(SSD1306_SETMULTIPLEX);                  // 0xA8
  		Oled_command(SSD1306_LCDHEIGHT - 1);
  	#endif

  	// following 3 satements are set by default, but sometimes
	// the display got the wrong commands. So we keep it..
	Oled_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3 <this is set by default>
  	Oled_command(0x00);                                  // no offset
  	Oled_command(SSD1306_SETSTARTLINE | 0x0);            // line #0 <this is set by default>

  	Oled_command(SSD1306_CHARGEPUMP);                    // 0x8D
  	if (vccstate == SSD1306_EXTERNALVCC) {
    	Oled_command(0x10);
	}
  	else {
		Oled_command(0x14);
	}

  	Oled_command(SSD1306_MEMORYMODE);                    // 0x20
  	Oled_command(0x00);                                  // 0x0 

  	Oled_command(SSD1306_SEGREMAP | 0x1);					// 0xA0 | 0x1
  	Oled_command(SSD1306_COMSCANDEC);

 	#if defined SSD1306_128_32
  		Oled_command(SSD1306_SETCOMPINS);                    // 0xDA
  		Oled_command(0x02);
  		Oled_command(SSD1306_SETCONTRAST);                   // 0x81
  		Oled_command(0x8F);

	#elif defined SSD1306_128_64
  		Oled_command(SSD1306_SETCOMPINS);                    // 0xDA
  		Oled_command(0x12);
  		Oled_command(SSD1306_SETCONTRAST);                   // 0x81
  		if (vccstate == SSD1306_EXTERNALVCC) {
			Oled_command(0x9F);
		}
  		else {
			Oled_command(0xCF);
		}

	#elif defined SSD1306_96_16
  		Oled_command(SSD1306_SETCOMPINS);                    // 0xDA
  		Oled_command(0x2);
  		Oled_command(SSD1306_SETCONTRAST);                   // 0x81
  		if (vccstate == SSD1306_EXTERNALVCC) {
			Oled_command(0x10);
		}
  		else {
			Oled_command(0xAF);
		}

	#endif

  	Oled_command(SSD1306_SETPRECHARGE);                  // 0xD9
  	if (vccstate == SSD1306_EXTERNALVCC) {
		Oled_command(0x22);
	}
  	else {
		Oled_command(0xF1);
	}

  	//Oled_command(SSD1306_SETVCOMDETECT);                 // 0xDB <unclear but appears to have set by default>
  	//Oled_command(0x40);

  	//Oled_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4 <this is set by default>
  	//Oled_command(SSD1306_NORMALDISPLAY);                 // 0xA6 <this is set by default>


	//Oled_command(SSD1306_DEACTIVATE_SCROLL);				// 0x2E (why adafruit?)

  	Oled_command(SSD1306_DISPLAYON);//--turn on oled panel
}

//******************************************

#if !defined NO_SCROLL

	void Oled_StartScrollRight(uint8_t start, uint8_t stop) {
  		Oled_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
  		Oled_command(0X00);
  		Oled_command(start);  // start page
  		Oled_command(0X00);
  		Oled_command(stop);   // end page
  		Oled_command(0X00);
  		Oled_command(0XFF);
  		Oled_command(SSD1306_ACTIVATE_SCROLL);
	}

	void Oled_StartScrollLeft(uint8_t start, uint8_t stop) {
  		Oled_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
  		Oled_command(0X00);
  		Oled_command(start);
  		Oled_command(0X00);
  		Oled_command(stop);
  		Oled_command(0X00);
  		Oled_command(0XFF);
  		Oled_command(SSD1306_ACTIVATE_SCROLL);
	}

	void Oled_StartScrollDiagRight(uint8_t start, uint8_t stop) {
  		Oled_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
  		Oled_command(0X00);
		Oled_command(SSD1306_LCDHEIGHT);
  		Oled_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  		Oled_command(0X00);
  		Oled_command(start);
  		Oled_command(0X00);
  		Oled_command(stop);
  		Oled_command(0X01);
  		Oled_command(SSD1306_ACTIVATE_SCROLL);
	}

	void Oled_StartScrollDiagLeft(uint8_t start, uint8_t stop) {
  		Oled_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
  		Oled_command(0X00);
  		Oled_command(SSD1306_LCDHEIGHT);
  		Oled_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  		Oled_command(0X00);
  		Oled_command(start);
  		Oled_command(0X00);
  		Oled_command(stop);
  		Oled_command(0X01);
  		Oled_command(SSD1306_ACTIVATE_SCROLL);
	}

	void Oled_StopScroll(void) {
  		Oled_command(SSD1306_DEACTIVATE_SCROLL);
	}

#endif  // end if !NO_SCROLL

//*************************************

void Oled_Dim(uint8_t vccstate, uint8_t dim) {
  	uint8_t contrast;
  	if (dim & 1)
    	contrast = 0; // Dimmed display
  	else {
    	if (vccstate == SSD1306_EXTERNALVCC)
      		contrast = 0x9F;
    	else
      		contrast = 0xCF;
  		}
  	// the range of contrast to too small to be really useful
  	// it is useful to dim the display
  	Oled_command(SSD1306_SETCONTRAST);
  	Oled_command(contrast);
}


void Oled_SetTextWrap(uint8_t w) {
	wrap = w & 1;
}

void Oled_InvertDisplay(uint8_t i) {
  	if (i & 1)
    	Oled_command(SSD1306_INVERTDISPLAY_);
  	else
    	Oled_command(SSD1306_NORMALDISPLAY);
}

void Oled_GotoXY(uint8_t x, uint8_t y) {
  	if((x > SSD1306_LCDWIDTH / 6) || y > SSD1306_LCDHEIGHT / 8)
    	return;
  	x_pos = x;
  	y_pos = y;
}


void Oled_PutC(uint8_t c) {
  	uint8_t i, font_c;
  	if((c <FONT_START) || (c > FONT_LAST)) {
    	c = FONT_LAST;
  	}
  	Oled_command(SSD1306_COLUMNADDR);
  	Oled_command(6 * (x_pos - 1));
  	Oled_command(6 * (x_pos - 1) + 4); // Column end address (127 = reset)

  	Oled_command(SSD1306_PAGEADDR);
  	Oled_command(y_pos - 1); // Page start address (0 = reset)
  	Oled_command(y_pos - 1); // Page end address
  
  	I2C_startBit();
  	I2C_sendData(SSD1306_I2C_ADDRESS);
  	I2C_sendData(0x40);
  
  	for(i = 0; i < 5; i++ ) {
    	font_c = Font[(c - FONT_START) * 5 + i];
      	I2C_sendData(font_c);
  	}
  	I2C_stopBit();

  	#if defined SSD1306_128_64 || defined SSD1306_128_32
  		x_pos = x_pos % 21 + 1;
  		if (wrap && (x_pos == 1))
    		#if defined SSD1306_128_64
      			y_pos = y_pos % 8 + 1;
    		#else
      			y_pos = y_pos % 4 + 1;
    		#endif

  	#else
    	x_pos = x_pos % 16 + 1;
    	if (wrap && (x_pos == 1))
      		y_pos = y_pos % 2 + 1;
  	#endif
}


void Oled_PutCustomC(uint8_t *c) {
  	uint8_t i, line;
  	Oled_command(SSD1306_COLUMNADDR);
  	Oled_command(6 * (x_pos - 1));
  	Oled_command(6 * (x_pos - 1) + 4); // Column end address (127 = reset)

  	Oled_command(SSD1306_PAGEADDR);
  	Oled_command(y_pos - 1); // Page start address (0 = reset)
  	Oled_command(y_pos - 1); // Page end address
  
  	I2C_startBit();
  	I2C_sendData(SSD1306_I2C_ADDRESS);
  	I2C_sendData(0x40);
  
  	for(i = 0; i < 5; i++ ) {
    	line = c[i];
    	I2C_sendData(line);
  	}
  	I2C_stopBit();

  	#if defined SSD1306_128_64 || defined SSD1306_128_32
  		x_pos = x_pos % 21 + 1;
  		if (wrap && (x_pos == 1))
    		#if defined SSD1306_128_64
      			y_pos = y_pos % 8 + 1;
    		#else
      			y_pos = y_pos % 4 + 1;
    		#endif
  	#else
	    x_pos = x_pos % 16 + 1;
    	if (wrap && (x_pos == 1))
      	y_pos = y_pos % 2 + 1;
  	#endif

}

void Oled_Print(const uint8_t *s) { // added \r and \n functionality
	uint8_t i = 0;
  	while (s[i] != '\0'){
    	if (s[i] == ' ' && x_pos == 1) {
	    	i++;
		}
	    else {
			if (s[i] == '\n' || s[i] == '\r') { //LF or CR ?
				x_pos = 1;
				if (s[i] == '\n') {
					#if defined SSD1306_128_64
						y_pos = y_pos % 8 + 1;
					#elif defined SSD1306_128_32
						y_pos = y_pos % 4 + 1;
					#elif defined SSD1306_96_16
						y_pos = y_pos % 2 + 1;
					#endif
				}
				i++;
			}
			else {
    			Oled_PutC(s[i++]);
			}
	  	}
	}
}

void Oled_ClearDisplay(uint8_t c) {
  	uint16_t i;
  	Oled_command(SSD1306_COLUMNADDR);
  	Oled_command(0);    // Column start address
	#if defined SSD1306_128_64 || defined SSD1306_128_32
  		Oled_command(127);  // Column end address
  	#else
    	Oled_command(95); // Column end address
  	#endif

  	Oled_command(SSD1306_PAGEADDR);
  	Oled_command(0);   // Page start address (0 = reset)
  	#if defined SSD1306_128_64
  		Oled_command(7);   // Page end address
  	#elif defined SSD1306_128_32
  		Oled_command(3);   // Page end address
  	#elif defined SSD1306_96_16
  		Oled_command(1);   // Page end address
  	#endif

  	I2C_startBit();
  	I2C_sendData(SSD1306_I2C_ADDRESS);
  	I2C_sendData(0x40);

  	for(i = 0; i < SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8; i++ )
    	I2C_sendData(c);
  	I2C_stopBit();
}



void Oled_Printscaled(const uint8_t *s, uint8_t fontsize) { // added \r and \n functionality
	uint8_t i = 0, j, k, m, font_c;
	uint32_t scale_font32;

	if (fontsize < 2) {
		Oled_Print(s);
		return;
	}
	if (fontsize > 4) fontsize = 4;
  	while (s[i] != '\0'){
    	if (s[i] == ' ' && x_pos == 1) {
	      i++;
		}
	    else {
			if (s[i] == '\n' || s[i] == '\r') { //LF or CR ?
				x_pos = 1;
				if (s[i] == '\n') {
					y_pos += fontsize;
					#if defined SSD1306_128_64
						y_pos = (y_pos - 1) % 8  + 1;
					#elif defined SSD1306_128_32
						y_pos = (y_pos - 1) % 4  + 1;
					#elif defined SSD1306_96_16
						y_pos = (y_pos - 1) % 2  + 1;
					#endif
					if (y_pos<fontsize) y_pos=fontsize;
				}
				i++;
			}
			else { 
    			Oled_command(0x20);    // vert mode
   				Oled_command(0x01);
   				Oled_command(0x21);     //col addr
				if (((fontsize*6+1) * (x_pos-1) + fontsize*5) >  SSD1306_LCDWIDTH) {
					x_pos = 1;
					if (wrap) {
						y_pos += fontsize;
						#if defined SSD1306_128_64
							y_pos = (y_pos - 1) % 8  + 1;
						#elif defined SSD1306_128_32
							y_pos = (y_pos - 1) % 4  + 1;
						#elif defined SSD1306_96_16
							y_pos = (y_pos - 1) % 2  + 1;
						#endif
						//if (y_pos<fontsize) y_pos=fontsize;
					}
				}
				if (y_pos<fontsize) y_pos=fontsize;
   				Oled_command((fontsize*6+1) * (x_pos-1) ); //col start
   				Oled_command((fontsize*6+1) * (x_pos-1) + fontsize*5 - 1);  //col end
    			Oled_command(0x22);    //0x22
   				Oled_command(y_pos - fontsize); // Page start
   				Oled_command(y_pos - 1); // Page end
    
       			I2C_startBit();
       			I2C_sendData(SSD1306_I2C_ADDRESS);            // address
        		I2C_sendData(0x40);

				for(j = 0; j < 5; j++ ) { // fill scale_font32 bit
					scale_font32 = 0;
    				font_c = Font[(s[i] - FONT_START) * 5 + j]; // get font
  					for (k=0; k<8; k++) {
						if (font_c & (1<<k)) { //test bit(k)
							for (m=0; m<fontsize; m++) { // expand height fontsize times
								scale_font32 |=  ((uint32_t) 1<<(k*fontsize + m)); // casting of '1' is important here!
							}
						}
					}

					// draw char scaled
					for (k=0; k<fontsize; k++) {
						for (m=0; m<fontsize; m++) {
							I2C_sendData((scale_font32>>(m*8))&0xFF); 
						}
					}
				}
       			I2C_stopBit();
        	
   				Oled_command(0x20);      // horizontal mode
   				Oled_command(0x00);  
				x_pos++;
				i++;
			}
	  	}
	}
}

void	Oled_rotate(uint8_t rotate) { // rotate = 0 or 1. 1 = rotate 180deg
			Oled_command(SSD1306_SEGREMAP | !(rotate&0x01));					// 0xA0 
  			Oled_command(SSD1306_COMSCANINC | ((!(rotate&0x01))<<3));			// 0xC0
}