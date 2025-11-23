/******************************************************************************
 SSD1306 OLED driver include file                               *
 Software I2C driver                                                          *
 The driver is for I2C mode only.                                             *
                    														  *
 ARV nov 2025																  *
																			  *
 																			  *
*******************************************************************************/

#ifndef SSD1306_H
#define SSD1306_H

//#define FONT_NUMBERS_ONLY	// uncomment for number font only
#define NO_SCROLL			// uncomment for no scroll
#include <htc.h>
#include <stdint.h>
#include "I2C_soft.h"
#include "font.h"



uint8_t x_pos = 1, y_pos = 1, wrap = 1;

#if !defined SSD1306_I2C_ADDRESS
	#define SSD1306_I2C_ADDRESS   0x78
#endif
#if !defined SSD1306_SWITCHCAPVCC
	#define SSD1306_SWITCHCAPVCC  0x02
#endif
#if !defined SSD1306_128_32 && !defined SSD1306_96_16
	#define SSD1306_128_64
#endif
#if defined SSD1306_128_32 && defined SSD1306_96_16
  	#error "Only one SSD1306 display can be specified at once"
#endif

#if defined SSD1306_128_64
  	#define SSD1306_LCDWIDTH            128
  	#define SSD1306_LCDHEIGHT            64
#endif
#if defined SSD1306_128_32
  	#define SSD1306_LCDWIDTH            128
  	#define SSD1306_LCDHEIGHT            32
#endif
#if defined SSD1306_96_16
  	#define SSD1306_LCDWIDTH             96
  	#define SSD1306_LCDHEIGHT            16
#endif

#define SSD1306_SETCONTRAST          0x81
#define SSD1306_DISPLAYALLON_RESUME  0xA4
#define SSD1306_DISPLAYALLON         0xA5
#define SSD1306_NORMALDISPLAY        0xA6
#define SSD1306_INVERTDISPLAY_       0xA7
#define SSD1306_DISPLAYOFF           0xAE
#define SSD1306_DISPLAYON            0xAF
#define SSD1306_SETDISPLAYOFFSET     0xD3
#define SSD1306_SETCOMPINS           0xDA
#define SSD1306_SETVCOMDETECT        0xDB
#define SSD1306_SETDISPLAYCLOCKDIV   0xD5
#define SSD1306_SETPRECHARGE         0xD9
#define SSD1306_SETMULTIPLEX         0xA8
#define SSD1306_SETLOWCOLUMN         0x00
#define SSD1306_SETHIGHCOLUMN        0x10
#define SSD1306_SETSTARTLINE         0x40
#define SSD1306_MEMORYMODE           0x20
#define SSD1306_COLUMNADDR           0x21
#define SSD1306_PAGEADDR             0x22
#define SSD1306_COMSCANINC           0xC0
#define SSD1306_COMSCANDEC           0xC8
#define SSD1306_SEGREMAP             0xA0
#define SSD1306_CHARGEPUMP           0x8D
#define SSD1306_EXTERNALVCC          0x01
#define SSD1306_SWITCHCAPVCC         0x02

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL                      0x2F
#define SSD1306_DEACTIVATE_SCROLL                    0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A



// function declarations
void Oled_command(uint8_t c);
void Oled_Init(uint8_t vccstate, uint8_t i2caddr);
void Oled_StartScrollRight(uint8_t start, uint8_t stop);
void Oled_StartScrollLeft(uint8_t start, uint8_t stop);
void Oled_StartScrollDiagRight(uint8_t start, uint8_t stop);
void Oled_StartScrollDiagLeft(uint8_t start, uint8_t stop);
void Oled_StopScroll(void);
void Oled_Dim(uint8_t vccstate, uint8_t dim);
void Oled_SetTextWrap(uint8_t w);
void Oled_InvertDisplay(uint8_t i);
void Oled_GotoXY(uint8_t x, uint8_t y);
void Oled_PutC(uint8_t c);
void Oled_PutCustomC(uint8_t *c);
void Oled_Print(const uint8_t*s);
void Oled_ClearDisplay(uint8_t c);
void drawChar2(uint8_t fig, unsigned char y, unsigned char x);
void Oled_Printscaled(const uint8_t *s, uint8_t fontsize);
void Oled_rotate(uint8_t rotate);

#endif   
