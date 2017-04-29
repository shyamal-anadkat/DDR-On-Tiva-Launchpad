#include "menu_nav.h"

//*****************************************************************************
// GLOBAL VARIABLES
//*****************************************************************************
game_state_fsm game_state;
SELECTED_ITEM selected_item = PLAY_NOW;

extern bool Alert_Timer0B;


//*****************************************************************************
// FUNCTIONS
//*****************************************************************************

void update_ui_init_new_state(game_state_fsm new_state) {
	
 	switch(new_state) {
 		case MENU:
 			update_ui_init_main_menu();
 			break;
 		case PLAY:
			selected_item = NOTHING;
 			update_ui_init_play();
 			break;
 		case WIN:
 			//update_ui_init_win();
 			break;
 		case LOSE:
 			//update_ui_init_lose();
 			break;
		default:
			break;
 	}
}



void update_ui_init_main_menu() { 

	//	char menu[] = "MENU"; 	
	char msg1[] = "PLAY NOW";
	char msg2[] = "HIGH SCORES";
	
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	//	lcd_print_stringXY(menu,0,0, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	lcd_print_stringXY(msg1,2,2, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  lcd_print_stringXY(msg2,1,4, LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
	
	// DRAW ARROW
	lcd_draw_image(
                  37,            		  // X Pos
                  ddrlogoWidthPixels, // Image Horizontal Width
                  3,       				  	// Y Pos
                  ddrlogoHeightPixels,// Image Vertical Height
                  ddrlogoBitmaps, 		// Image
                  LCD_COLOR_ORANGE,      // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
}

void display_selected_menu_item() {
	
	switch(selected_item) {
		case PLAY_NOW:
			clear_line(5);
			draw_line(1);
			draw_line(3);
			break;
		case HIGH_SCORES:
			clear_line(1);
			draw_line(3);
			draw_line(5);
			break;
		default:
			break;
	}
}

void navigate_main_menu(uint16_t y_adc_data) {
		
	  if (y_adc_data >= y_up_threshold) {
				selected_item = PLAY_NOW;
		} 
		else if (y_adc_data <= y_down_threshold) {
				selected_item = HIGH_SCORES;
		}
		display_selected_menu_item();
}

void print_hit() {
	char hit[] = "HIT";
	lcd_print_stringXY(hit,10,10, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
}

void print_boo() {
	char boo[] = "BOO!";
	lcd_print_stringXY(boo,10,10, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
}

void clear_boo() {
	char miss[] = "BOOO!";
	lcd_print_stringXY(miss,10,10, LCD_COLOR_BLACK,LCD_COLOR_BLACK);
}

void print_miss() {
	char miss[] = "MISS!";
	lcd_print_stringXY(miss,10,10, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
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

	
// *******************************************************************************
// * UTILITY FUNCTIONS
// ********************************************************************************
	
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
