#include "ddr_animations.h"

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
void move_arrows(int dir, int speed, uint16_t fColor, uint16_t bColor) {}


	
	
void display_welcome_screen(void) {
			lcd_draw_image(
                  133,                // X Pos
                  ddrbwWidthPixels,   		// Image Horizontal Width
                  82,                // Y Pos
                  ddrbwHeightPixels,    // Image Vertical Height
                  ddrbwBitmaps, 		    // Image
                  LCD_COLOR_BLACK,     // Foreground Color
                  LCD_COLOR_WHITE     // Background Color
                ); 
}




