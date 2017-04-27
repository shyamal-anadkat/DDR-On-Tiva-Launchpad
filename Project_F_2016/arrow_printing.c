#include "arrow_printing.h"

// ASSUMES Y POSITION OF ARROW HAS ALREADY BEEN UPDATED
void print_arrow(arrow_t *arrow) {
	uint16_t x_pos;
	const uint8_t *arrow_bitmap;
	
	switch(arrow->arrow_type) {
		case ARROW_DIR_UP:
			x_pos = ARROW_POS_X_UP;
			arrow_bitmap = up_arrowBitmaps;
			break;
		case ARROW_DIR_DOWN:
			x_pos = ARROW_POS_X_DOWN;
			arrow_bitmap = down_arrowBitmaps;
			break;
		case ARROW_DIR_LEFT:
			x_pos = ARROW_POS_X_LEFT;
			arrow_bitmap = left_arrowBitmaps;
			break;
		case ARROW_DIR_RIGHT:
			x_pos = ARROW_POS_X_RIGHT;
			arrow_bitmap = right_arrowBitmaps;
			break;
	}
	
	// DRAW ARROW
	if(arrow->y_pos <= (ARROW_POS_END_Y)) {
		lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow->y_pos,        // Y Pos
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// Image
                  arrow->color,        // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
	}
	
		// CLEAR GLITCHY BLUE TRAIL : KEEP THE TRAIL ?
		/*lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow.y_pos - ARROW_HEIGHT + 1,// Y Pos of bottom of image
                  ARROW_HEIGHT,  			// Image Vertical Height
                  0x0, 								// DON'T CARE
                  LCD_COLOR_BLACK,    // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                ); */
}

void print_top_arrow(arrow_dir_t arrow_dir) {
	uint16_t x_pos;
	uint16_t color;
	const uint8_t *arrow_bitmap;
	
		switch(arrow_dir) {
		case ARROW_DIR_UP:
			x_pos = ARROW_POS_X_UP;
			arrow_bitmap = up_arrowBitmaps;
			color = ARROW_TOP_COLOR_UP;
			break;
		case ARROW_DIR_DOWN:
			x_pos = ARROW_POS_X_DOWN;
			arrow_bitmap = down_arrowBitmaps;
			color = ARROW_TOP_COLOR_DOWN;
			break;
		case ARROW_DIR_LEFT:
			x_pos = ARROW_POS_X_LEFT;
			arrow_bitmap = left_arrowBitmaps;
			color = ARROW_TOP_COLOR_LEFT;
			break;
		case ARROW_DIR_RIGHT:
			x_pos = ARROW_POS_X_RIGHT;
			arrow_bitmap = right_arrowBitmaps;
			color = ARROW_TOP_COLOR_RIGHT;
			break;
	}
	
	lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  ARROW_POS_TRGT_Y,   // Y Pos
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// Image
                  color,        			// Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
}


// ASSUMES Y POSITION OF ARROW HAS ALREADY BEEN UPDATED
void clear_arrow(arrow_t *arrow) {
	uint16_t x_pos;
	const uint8_t *arrow_bitmap;
	
	switch(arrow->arrow_type) {
		case ARROW_DIR_UP:
			x_pos = ARROW_POS_X_UP;
			arrow_bitmap = up_arrowBitmaps;
			break;
		case ARROW_DIR_DOWN:
			x_pos = ARROW_POS_X_DOWN;
			arrow_bitmap = down_arrowBitmaps;
			break;
		case ARROW_DIR_LEFT:
			x_pos = ARROW_POS_X_LEFT;
			arrow_bitmap = left_arrowBitmaps;
			break;
		case ARROW_DIR_RIGHT:
			x_pos = ARROW_POS_X_RIGHT;
			arrow_bitmap = right_arrowBitmaps;
			break;
	}
	
	// DRAW ARROW
	if(arrow->y_pos <= (ARROW_POS_END_Y)) {
		lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow->y_pos,        // Y Pos
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// Image
                  LCD_COLOR_BLACK,    // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
	}
}