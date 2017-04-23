#include "ddr_animations.h"
#include "timers.h"


void lcd_print_stringXY(
    char *msg, 
    int8_t X,
		int8_t Y,
    uint16_t fg_color, 
    uint16_t bg_color
)
{
	int len = strlen(msg);	// get the length of the message passed in using strlen in string.h
	
	int Xpixels;	// convert X to pixels to call lcd_draw_image
	int Ypixels;  // convert Y to pixels to call lcd_draw_image
	
	int i;		// for the for loop
	
	int currentX = X;		// to preserve the current x
	int currentY = Y;		// to preserve the current y
	
	int val;						// C ascii value of the character
	int image_bitmap;			// convert it to the image bitmap from lookup-table given above
	
	// for loop to go through the characters in the given string
	for(i = 0; i < len; i++) {
		
		// wrap around if statements
		if(currentX == 14) {		// if the value of the current X is greater than 13
			if(msg[i] == 32) {		// if the ascii value of space is our characte
				i = i + 1;					// go to the next character to start the next line
			}
			currentX = X;					// update the currentX to the original X			
			currentY = currentY+1;	// change Y to go to the next line
		}
		
		if(currentY == 20 ) {		// if the value of current Y is greater than 19
			currentY = 0;					// go to the 0th index of Y or simply, the top of the screen
		}
		
		// get the ascii/bitmap/pixel values
		val = (int) msg[i];			// get the ascii value of the character
		image_bitmap = (val - 32)*48;	// convert to the bitmap value 
		
		Xpixels = 240 - ((currentX+1)*17 ) ;	// based on the current index, change the pixel of X. The width changes with the X coordinate. 
		Ypixels = 320 - ((currentY+1)*16 ); 	// based on the current index, change the pixel of Y. The height changes with the Y coordinate. 
		
		// call lcd_draw_image, based on the image bitmap and X and Y pixels
	lcd_draw_image(
		Xpixels, 
		17, 
		Ypixels, 
		16, 
		&(sitkaSmall_12ptBitmaps[image_bitmap]), 
		fg_color, 
		bg_color
	);
		
		// increment the index of X
		currentX++;
	
  }
}

void printMenu() { 

	char menu[] = "MENU"; 	
	char msg1[] = "PLAY NOW";
	char msg2[] = "HIGH SCORES";
	
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	lcd_print_stringXY(menu,0,0, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	lcd_print_stringXY(msg1,2,4, LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
  lcd_print_stringXY(msg2,1,7, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
}

//void print_PlayNow() {
//	char playnow[] = "PLAY NOW" ;
//	char score[] = "SCORE"; 
//	
//	lcd_print_stringXY(playnow,0, 0, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
//	lcd_print_stringXY(score, 10,18, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
//	
//}


void draw_line(uint8_t y) {
	char dot[] = "--------------";
	uint8_t x = 0; 
	//while(x >= 0) {
		lcd_print_stringXY(dot, x, y, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
		//x--;
	//}
}




void select_menuItem(int item) {
	if(item) {
		//PLAY NOW HIGHLIGHTED
		draw_line(3);
		draw_line(5);
	} else{
	 // HIGH SCORES HIGHLIGHTED 
	 draw_line(6);
	 draw_line(8);
 }
}
