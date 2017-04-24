#include "menu_nav.h"

//*****************************************************************************
// GLOBAL VARIABLES
//*****************************************************************************
game_state_fsm game_state;
SELECTED_ITEM selected_item = PLAY_NOW;





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

	char menu[] = "MENU"; 	
	char msg1[] = "PLAY NOW";
	char msg2[] = "HIGH SCORES";
	
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	lcd_print_stringXY(menu,0,0, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	lcd_print_stringXY(msg1,2,4, LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
  lcd_print_stringXY(msg2,1,7, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
}



void display_selected_menu_item() {
	
	switch(selected_item) {
		case PLAY_NOW:
			clear_line(6);
			clear_line(8);
			draw_line(3);
			draw_line(5);
			break;
		case HIGH_SCORES:
			clear_line(3);
			clear_line(5);
			draw_line(6);
			draw_line(8);
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
