#include "ddr_animations.h"

arrow_t arrows_on_screen[MAX_ARROWS_ON_SCREEN];
uint8_t num_arrows_on_screen;
bool playSelected;

void animate_arrows() {
	uint8_t i;
	uint16_t y_pos;
	
	// TODO: Check GAMESTATE_FSM
	
	// MOVE ALL ONSCREEN ARROWS UP BY 1
	for(i = 0; i < num_arrows_on_screen; i++) {
		arrow_t* arrow = &arrows_on_screen[i];
		arrow->y_pos++;
		print_arrow(*arrow);
	}
}


// RETURNS FALSE IF TOO MANY ARROWS ADDED
bool add_arrow(arrow_dir_t dir) {
	arrow_t arrow;
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow.arrow_type = dir;
	arrow.y_pos = ARROW_POS_START_Y;
	
	// Return false if no more arrows can be added to the screen
	if(num_arrows_on_screen >= MAX_ARROWS_ON_SCREEN) return false;
	else {
		arrows_on_screen[num_arrows_on_screen++] = arrow;
		return true;
	}
}

bool add_two_arrows(arrow_dir_t dir1, arrow_dir_t dir2) {
	arrow_t arrow1;
	arrow_t arrow2;
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow1.arrow_type = dir1;
	arrow1.y_pos = ARROW_POS_START_Y;
	arrow2.arrow_type = dir2;
	arrow2.y_pos = ARROW_POS_START_Y;

	// Return false if no more arrows can be added to the screen
	if(num_arrows_on_screen >= MAX_ARROWS_ON_SCREEN) return false;
	else {
		arrows_on_screen[num_arrows_on_screen++] = arrow1;
		arrows_on_screen[num_arrows_on_screen++] = arrow2;
		return true;
	}
}

// ASSUMES Y POSITION OF ARROW HAS ALREADY BEEN UPDATED
void print_arrow(arrow_t arrow) {
	uint16_t x_pos;
	const uint8_t *arrow_bitmap;
	
	switch(arrow.arrow_type) {
		case ARROW_UP:
			x_pos = ARROW_POS_X_UP;
			arrow_bitmap = up_arrowBitmaps;
			break;
		case ARROW_DOWN:
			x_pos = ARROW_POS_X_DOWN;
			arrow_bitmap = down_arrowBitmaps;
			break;
		case ARROW_LEFT:
			x_pos = ARROW_POS_X_LEFT;
			arrow_bitmap = left_arrowBitmaps;
			break;
		case ARROW_RIGHT:
			x_pos = ARROW_POS_X_RIGHT;
			arrow_bitmap = right_arrowBitmaps;
			break;
	}
	
	// DRAW ARROW
	lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow.y_pos,        // Y Pos
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// Image
                  LCD_COLOR_BLUE,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
	
	// CLEAR GLITCHY BLUE TRAIL
		lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow.y_pos - ARROW_HEIGHT + 1,// Y Pos of bottom of image
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// DON'T CARE
                  LCD_COLOR_BLACK,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
}