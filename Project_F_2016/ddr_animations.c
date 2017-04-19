#include "ddr_animations.h"
#include "timers.h"

//*****************************************************************************
// Printing arrows on the lcd screen  
//*****************************************************************************
void print_arrows(void) {
	
		const uint16_t y_pos = 275;
		lcd_clear_screen(LCD_COLOR_BLACK); 	// clear the screen
	
		// LEFT ARROW
		lcd_draw_image(
                  195,                // X Pos
                  40,   							// Image Horizontal Width
                  y_pos,              // Y Pos
                  39,  								// Image Vertical Height
                  left_arrowBitmaps, 	// Image
                  LCD_COLOR_BLUE,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                ); 
		// DOWN ARROW 
		lcd_draw_image(
                  150,                // X Pos
                  40,   							// Image Horizontal Width
                  y_pos,              // Y Pos
                  39,  								// Image Vertical Height
                  down_arrowBitmaps, 	// Image
                  LCD_COLOR_BLUE,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                ); 
		// UP ARROW 
		lcd_draw_image(
                  105,                // X Pos
                  40,   							// Image Horizontal Width
                  y_pos,              // Y Pos
                  39,  								// Image Vertical Height
                  up_arrowBitmaps, 		// Image
                  LCD_COLOR_BLUE,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                ); 
		// RIGHT ARROW 
		lcd_draw_image(
                  60,                 // X Pos
                  40,   							// Image Horizontal Width
                  y_pos,              // Y Pos
                  39,  								// Image Vertical Height
                  right_arrowBitmaps, // Image
                  LCD_COLOR_BLUE,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                ); 
	
}


// animation for arrows (bottom of screen to top) 
// Takes in direction of arrow, color and speed params
void move_arrow(int dir, int speed, uint16_t fColor, uint16_t bColor) {
		
		//TODO: functionality for dir and speed
		
		//TODO: make these static/global
		uint16_t y_max = 275;
	
		uint16_t x_min = 195; 
		uint16_t y_min = 5;
	
		uint16_t x_pos; 
		uint16_t y_pos; 
		const uint8_t *arrow_image;
	
		switch(dir) {
			
		 case 0 :
				x_min = 195;
				break; 
		
		 case 1 :
				x_min = 150;
				break; 
		 
		 case 2: 
				x_min = 105;
				break;
		 
		 case 3:
				x_min = 60;
				break;
		 
		 default : ;
		}
		
		x_pos = x_min; 
		y_pos = y_min;
				
		//choose arrow based on direction param
	  // 0: left || 1: down || 2: up || 3: right
		arrow_image = (dir == 0) ? left_arrowBitmaps : (dir == 1) 
			? down_arrowBitmaps : (dir == 2) ? up_arrowBitmaps : right_arrowBitmaps;
	
		lcd_clear_screen(LCD_COLOR_BLACK); 	// clear the screen
		while (y_pos < y_max) {
				
				// this part clears the arrow at (y-1)
				lcd_draw_image(
                  x_pos,              // X Pos
                  40,   							// Image Horizontal Width TODO:
                  y_min,              // Y Pos
                  y_pos-1,  					// Image Vertical Height
                  arrow_image, 				// Image
                  bColor,    				  // Foreground Color
                  bColor              // Background Color
                ); 
			
			  // Animate the given arrow 
				lcd_draw_image(
                  x_pos,              // X Pos
                  40,   							// Image Horizontal Width TODO:
                  y_pos,              // Y Pos
                  39,  								// Image Vertical Height
                  arrow_image, 				// Image
                  fColor,    				  // Foreground Color
                  bColor              // Background Color
                ); 
			
				//	wait for (2nd param) number of ticks [refer to ICE 13]
				//	timer funtionality for wait, control the speed with ticks 
				gp_timer_wait(TIMER0_BASE, speed);
				
			y_pos++; //increment y for animating effect 
		}
		
}

void display_welcome_screen(void) {
			lcd_draw_image(
                  133,                // X Pos
                  ddrbwWidthPixels,   // Image Horizontal Width
                  82,                	// Y Pos
                  ddrbwHeightPixels,  // Image Vertical Height
                  ddrbwBitmaps, 		  // Image
                  LCD_COLOR_BLACK,    // Foreground Color
                  LCD_COLOR_WHITE     // Background Color
                ); 
}




