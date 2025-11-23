
/*********************************

	Conway's LIFE
	
	ARV 23 november 2025

**********************************/

#include "life_bit.h"
#include "oledlib.h"

// Fill the grid with random nubers
// random numbers from timer1 as seed
void initGrid(uint8_t pattern) {
	srand(TMR1H<<8|TMR1L);
	int x, y;
    for (y=0; y<HEIGHT; y++) {
        for (x=0; x<WIDTH; x++) {
            if (pattern) grid[x][y] = rand() % 256;
			else grid[x][y] = 0;
        }
    }
}

// This is a repetitive grid
void initGrid_pattern1() {

	initGrid(0);

//	grid[0][0] = 0;
//	grid[1][0] = 0;
//	grid[2][0] = 0;
//	grid[3][0] = 0;
//	grid[0][1] = 0;
//	grid[1][1] = 0;
//	grid[2][1] = 0;
//	grid[3][1] = 0;
//	grid[0][2] = 0;
	grid[1][2] = 0x18;
	grid[2][2] = 0x18;
//	grid[3][2] = 0;
//	grid[0][3] = 0;
	grid[1][3] = 0x28;
	grid[2][3] = 0x14;
//	grid[3][3] = 0;
//	grid[0][4] = 0;
	grid[1][4] = 0x20;
	grid[2][4] = 0x04;
//	grid[3][4] = 0;
	grid[0][5] = 0x01;
	grid[1][5] = 0xA0;
	grid[2][5] = 0x05;
	grid[3][5] = 0x80;
	grid[0][6] = 0x01;
	grid[1][6] = 0xA9;
	grid[2][6] = 0x95;
	grid[3][6] = 0x80;
//	grid[0][7] = 0;
	grid[1][7] = 0x2A;
	grid[2][7] = 0x54;
//	grid[3][7] = 0;
//	grid[0][8] = 0;
	grid[1][8] = 0x2A;
	grid[2][8] = 0x54;
//	grid[3][8] = 0;
	grid[0][9] = 0x01;
	grid[1][9] = 0xA9;
	grid[2][9] = 0x95;
	grid[3][9] = 0x80;
	grid[0][10] = 0x01;
	grid[1][10] = 0xA0;
	grid[2][10] = 0x05;
	grid[3][10] = 0x80;
//	grid[0][11] = 0;
	grid[1][11] = 0x20;
	grid[2][11] = 0x04;
//	grid[3][11] = 0;
//	grid[0][12] = 0;
	grid[1][12] = 0x28;
	grid[2][12] = 0x14;
//	grid[3][12] = 0;
//	grid[0][13] = 0;
	grid[1][13] = 0x18;
	grid[2][13] = 0x18;
//	grid[3][13] = 0;
//	grid[0][14] = 0;
//	grid[1][14] = 0;
//	grid[2][14] = 0;
//	grid[3][14] = 0;
//	grid[0][15] = 0;
//	grid[1][15] = 0;
//	grid[2][15] = 0;
//	grid[3][15] = 0;
}	

/* grid is a 32x16 bit pattern
 So we need 4 bytes per width (x direction)
 and 16 per height (y-direction)
 Oled receives 1 byte per frame, i.e 2 bits high
 a single bit is displayed as a 4x4 pixel on Oled*/
void printGrid(void) {
	uint8_t i, font_c;
	uint8_t	x, y, xbit;

	// prepare Oled for data:
  	Oled_command(SSD1306_COLUMNADDR);
  	Oled_command(0);
  	Oled_command(127); // Column end address (127 = reset)

  	Oled_command(SSD1306_PAGEADDR);
  	Oled_command(0); // Page start address (0 = reset)
  	Oled_command(7); // Page end address
  
  	I2C_startBit();
  	I2C_sendData(SSD1306_I2C_ADDRESS);
  	I2C_sendData(0x40);

	// send data
    for (y=0; y<HEIGHT; y+=2) {
	    for (x=0; x<WIDTH; x++) {
        	for (xbit = 0; xbit<8; xbit++) {
				font_c = 0;
				if (CHECK_BIT(grid[x][y], 7-xbit)) {
					font_c |= 0xF0;
				}
				if (CHECK_BIT(grid[x][y+1], 7-xbit)) {
					font_c |= 0x0F;
				}
				for (i=0; i<4; i++) {
					I2C_sendData(font_c);
				}
         	}
        }
    }

	// close Oled
	I2C_stopBit();
}




/* Count the neigbouring bits
 The grid is 'infinite' as the top and bottom rows are 'next' to eachother
 as well as the the left/right columns
 */
int countAliveNeighbours(int xc, int yc, int xbitc) {
    int count = 0, x, y;
    int	xbit_neighbour, x_neighbour, y_neighbour;
    for (y = -1; y <= 1; y++) {
        for (x = -1; x <= 1; x++) {
        		xbit_neighbour = (xbitc + x + 8) % 8;
        		if (xbitc+x < 0 || xbitc+x > 7) { // neigbouring byte
        			x_neighbour = (xc+x+WIDTH) % WIDTH;
        		}
        		else {
        			x_neighbour = xc;
        		}
            y_neighbour = (yc + y + HEIGHT) % HEIGHT;
            count += (grid[x_neighbour][y_neighbour]>>(7-xbit_neighbour))&0x01;
        }
    }
    count -= (grid[xc][yc]>>(7-xbitc))&0x01;
    return count;
}

/* This is the number cruncher of the routine
a newGrid is formed and -when finished- copied to the grid
 */
void updateGrid() {
    //uint8_t newGrid[WIDTH][HEIGHT];
    int	x, y, xbit, count;
    for (y=0; y<HEIGHT; y++) {
        for (x=0; x<WIDTH; x++) {
        		newGrid[x][y]=0;
				for (xbit=0; xbit<8; xbit++) {        	
            	count = countAliveNeighbours(x, y, xbit);
//            	if (grid[x][y] & (1<<(7-xbit))) {
            	if (CHECK_BIT(grid[x][y],7-xbit)) {
            		if (count==2 || count==3){
            			newGrid[x][y] |= 1<<(7-xbit);
            		}
            	}
            	else {
            		if (count==3) {
            			newGrid[x][y] |= 1<<(7-xbit);
            		}
            	}
         	}
        }
    }
    for (y=0; y<HEIGHT; y++) {
        for (x=0; x<WIDTH; x++) {
            grid[x][y] = newGrid[x][y];
        }
    }
}




