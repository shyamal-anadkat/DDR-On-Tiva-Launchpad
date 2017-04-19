#include "ddr_animations.h"
#include "timers.h"


#define LEFT 	0
#define DOWN 	1
#define UP   	2
#define RIGHT 3
//*****************************************************************************
// Printing arrows on the lcd screen  
//*****************************************************************************
void print_arrows(void) {
	
		const uint16_t y_pos = 274;
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
// Takes in direction of arrow, color, number of arrows to move[num] and speed params
void move_arrows(int num, int dir, int speed, uint16_t fColor, uint16_t bColor) {

		//x pos for different direction arrows
		const uint16_t x_min_left = 195; 
		const uint16_t x_min_down = 150;
	  const uint16_t x_min_up   = 105;
	  const uint16_t x_min_right= 60;
	
		bool moveLeft = false;
		bool moveDown = false;
		bool moveUp = false;
		bool moveRight = false;
	
		uint16_t x_pos_left; 
	  uint16_t x_pos_right; 
	  uint16_t x_pos_up;
	  uint16_t x_pos_down; 
	
		uint16_t y_pos;
		
		//TODO: make these static/global
		const uint16_t y_max = 275; //top of the screen 
		const uint16_t y_min = 5; 
		
		const uint8_t *arrow_image;
		
		switch(num) {
		 case 1:
			  moveLeft = true;
			  break;
		 case 2: 
				moveDown = true;
				moveLeft = true;
				break;
		 case 3:
				moveDown = true;
				moveLeft = true;
				moveUp = true;
				break;
		 case 4: 
				moveDown = true;
				moveLeft = true;
				moveUp =   true;
				moveRight = true;
				break;
		 default : ;
		}
		
		x_pos_left = x_min_left; 
		x_pos_right = x_min_right; 
		x_pos_down = x_min_down; 
		x_pos_up = x_min_up; 
		
		y_pos = y_min;
				
		// @Deprecated
		// choose arrow based on direction param
	  // 0: left || 1: down || 2: up || 3: right
		// arrow_image = (dir == 0) ? left_arrowBitmaps : (dir == 1) 
		// ? down_arrowBitmaps : (dir == 2) ? up_arrowBitmaps : right_arrowBitmaps;
	
		// lcd_clear_screen(LCD_COLOR_BLACK); 	// clear the screen
		while (y_pos < y_max) {
			
				//	wait for (2nd param) number of ticks [refer to ICE 13]
				//	timer funtionality for wait, control the speed with ticks 
				//  gp_timer_wait(TIMER0_BASE, speed);
			
				// this part clears the arrow at (y-1)
				lcd_draw_image(x_pos_left, 40, y_min, y_pos-1, left_arrowBitmaps, bColor, bColor); 
			  // Animate the given arrow 
			  lcd_draw_image(x_pos_left, 40, y_pos, 39, left_arrowBitmaps, fColor, bColor); 

				lcd_draw_image(x_pos_down, 40, y_min, y_pos-1, down_arrowBitmaps, bColor, bColor);  
				//gp_timer_wait(TIMER0_BASE, speed);
			  lcd_draw_image(x_pos_down, 40, y_pos, 39, down_arrowBitmaps, fColor, bColor); 	
			
				lcd_draw_image(x_pos_up, 40, y_min, y_pos-1, down_arrowBitmaps, bColor, bColor);  
				//gp_timer_wait(TIMER0_BASE, speed);
			  lcd_draw_image(x_pos_up, 40, y_pos, 39, down_arrowBitmaps, fColor, bColor); 
			
				lcd_draw_image(x_pos_right, 40, y_min, y_pos-1, down_arrowBitmaps, bColor, bColor);  
				//gp_timer_wait(TIMER0_BASE, speed);
			  lcd_draw_image(x_pos_right, 40, y_pos, 39, down_arrowBitmaps, fColor, bColor); 

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