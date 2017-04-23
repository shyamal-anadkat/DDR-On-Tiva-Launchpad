#include "ddr_animations.h"
#include "ddr_game.h"
#include "timers.h"

arrow_t arrows_on_screen[MAX_ARROWS_ON_SCREEN];
uint8_t num_arrows_on_screen;

//*****************************************************************************
// Updates the entire user interface according to the current state of the game
// Increments all of the onscreen arrows by 1
//*****************************************************************************
void update_ui(void) {
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
//	lcd_print_stringXY(playnow,0, 0, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
//	lcd_print_stringXY(score, 10,18, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
//	
//}

void draw_line(uint8_t y) {
	char dot[] = "--------------";
	uint8_t x = 0; 
		lcd_print_stringXY(dot, x, y, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
}

void clear_line(uint8_t y) {
	char dot[] = "--------------";
	uint8_t x = 0; 
	lcd_print_stringXY(dot, x, y, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
}


void select_menuItem(int item) {
	if(item) {
		
		//PLAY NOW HIGHLIGHTED
		clear_line(6);
		clear_line(8);
		draw_line(3);
		draw_line(5);
	} else{
		
	 // HIGH SCORES HIGHLIGHTED 
	 clear_line(3);
	 clear_line(5);
	 draw_line(6);
	 draw_line(8);
 }
}

void navigate_menu(uint16_t y_adc_data) {
		if (y_adc_data >= y_up_threshold) {
				select_menuItem(1);
		} 
		else if (y_adc_data <= y_down_threshold) {
				select_menuItem(0);
		} 			
	}