#include "arrow_printing.h"

extern uint16_t score;
extern bool Alert_Timer0B;

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


void print_top_arrow_hit(arrow_dir_t arrow_dir) {
	uint16_t x_pos;
	uint16_t color = LCD_COLOR_GREEN;
	const uint8_t *arrow_bitmap;
	
		switch(arrow_dir) {
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
		default:
			return;
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

void print_score(void) {
	char score_arr[4]; 
	//printf("Current Score: %d", score);
	sprintf(score_arr,"%ld",(long)score);
	lcd_print_stringXY("score:",5,0, LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
	lcd_print_stringXY(score_arr,11,0, LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
}

void clear_hit_miss_message(void){
	//this is to clear the hit/miss message on LCD
		static int ticks = 0;
		ticks++;
		if(ticks == PRINT_MESSAGE_DELAY){
			clear_boo();
			ticks = 0;
		}
}

void print_hit() {
	char hit[] = "HIT";
	lcd_print_stringXY(hit,11,10, LCD_COLOR_BLACK,LCD_COLOR_GREEN);
}

void print_boo() {
	char boo[] = "BOO";
	lcd_print_stringXY(boo,11,10, LCD_COLOR_WHITE,LCD_COLOR_ORANGE);
}

void clear_boo() {
	char miss[] = "MISS!";
	lcd_print_stringXY(miss,10,10, LCD_COLOR_BLACK,LCD_COLOR_BLACK);
}

void print_miss() {
	char miss[] = "MISS";
	lcd_print_stringXY(miss,10,10, LCD_COLOR_WHITE,LCD_COLOR_RED);
}

void print_hit_second() {
		print_hit();
}

void print_boo_second() {
		print_boo();
}

void print_miss_second() {
		print_miss();
}


uint16_t random_lcd_color(void) {
    // Note: Subtract 1 from LCD_NUM_COLORS because we're excluding LCD_COLOR_BLACK (since it
    // makes the arrow invisible)
    uint8_t rand_int = rand() % LCD_NUM_COLORS - 1;
    uint16_t lcd_color_array[LCD_NUM_COLORS - 1] = {LCD_COLOR_WHITE, LCD_COLOR_RED,
    LCD_COLOR_GREEN, LCD_COLOR_GREEN2, LCD_COLOR_BLUE, LCD_COLOR_BLUE2, LCD_COLOR_YELLOW,
    LCD_COLOR_ORANGE, LCD_COLOR_CYAN, LCD_COLOR_MAGENTA, LCD_COLOR_GRAY, LCD_COLOR_BROWN};
   
    return lcd_color_array[rand_int];
}


