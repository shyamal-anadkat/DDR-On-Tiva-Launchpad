#include "menu_nav.h"

//*****************************************************************************
// GLOBAL VARIABLES
//*****************************************************************************
game_state_fsm game_state;
SELECTED_ITEM selected_item = PLAY_NOW;

extern bool Alert_Timer0B;
bool backSelected;


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
 			update_ui_init_win();
 			break;
 		case LOSE:
 			update_ui_init_lose();
 			break;
		case HIGH_SCORE:
			update_ui_init_high_score();
			break; 
		default:
			break;
 	}
}

void update_ui_init_main_menu() { 

	char msg1[] = "PLAY NOW";
	char msg2[] = "HIGH SCORES";
	
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	lcd_print_stringXY(msg1,menu_play_now_x,menu_play_now_y, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  lcd_print_stringXY(msg2,menu_high_scores_x,menu_high_scores_y, LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
	
	// DRAW DOPE DDR LOGO/IMAGE
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

void update_ui_high_scores(void) {
	uint8_t touch_event;
	uint16_t x,y;
	touch_event = ft6x06_read_td_status();
	if(touch_event > 0) {
		x = ft6x06_read_x();
		y = ft6x06_read_y();
	} else {
		x = y = 256;
	}
	if(y <= back_upper_bound) {
		//CODE TO DISPLAY MAIN MENU
		game_state = MENU;
	}
}

void display_selected_menu_item() {
	
	switch(selected_item) {
		case PLAY_NOW:
			clear_line(menu_high_scores_y + offset);
			draw_line(menu_play_now_y - offset);
			draw_line(menu_high_scores_y - offset);
			break;
		case HIGH_SCORES:
			clear_line(menu_play_now_y - offset);
			draw_line(menu_high_scores_y - offset);
			draw_line(menu_high_scores_y + offset);
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

void print_high_scores() {
	
	// character arrays for the text
	char h[] = "HIGH";
	char s[] = "SCORES: ";
	char lon[] = "LONGEST";
	char time[] = "TIME: ";
	char game[] = "GAME";
	char mode[] = "MODE: ";
	char back[] = "BACK"; 
	// for the boxes
	char dot[] = "--------------";
	
	// clear the screen
	lcd_clear_screen(LCD_COLOR_BLACK);
	
	// print statements for printing to the high score screens with macros
	lcd_print_stringXY(h, high_screen_x,high_screen_y, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	lcd_print_stringXY(s, score_screen_x,score_screen_y, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	lcd_print_stringXY(lon,longest_screen_x, longest_screen_y, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	lcd_print_stringXY(time, time_screen_x,time_screen_y, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
  lcd_print_stringXY(game,game_screen_x,game_screen_y, LCD_COLOR_RED,LCD_COLOR_BLACK);
	lcd_print_stringXY(mode, mode_screen_x,mode_screen_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
	lcd_print_stringXY(back,back_screen_x, back_screen_y, LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
	
	lcd_print_stringXY(dot, draw_line_x, (back_screen_y - 1), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
}

void print_pause_screen() {
	
	char dot[] = "--------------";
	
	char msg1[] = "CONTINUE";
	char msg2[] = "MENU";
	
	// clear screen 
	lcd_clear_screen(LCD_COLOR_BLACK);
	
	// prints messages 1 and 2 with MACROS
	lcd_print_stringXY(msg1,pause_screen_continue_x,pause_screen_continue_y, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  lcd_print_stringXY(msg2,pause_screen_menu_x,pause_screen_menu_y, LCD_COLOR_RED,LCD_COLOR_BLACK);
	
	// 4 lines below for drawing the boxes, WITH MACROS
	lcd_print_stringXY(dot, draw_line_x, (pause_screen_continue_y - offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	lcd_print_stringXY(dot, draw_line_x, (pause_screen_continue_y + offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	
	lcd_print_stringXY(dot, draw_line_x, (pause_screen_menu_y - offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	lcd_print_stringXY(dot, draw_line_x, (pause_screen_menu_y + offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
}


//void print_win() {
//	char win[] = "YOU WON!!!";
//	
//	int8_t x = 0; 
//	
//	lcd_clear_screen(LCD_COLOR_BLACK);
//	
//	for(x = 0; x <= 4; x++){
//			lcd_print_stringXY(win, x, win_screen_y, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
//		if( x <4){ 
//			lcd_print_stringXY(win, x-1, win_screen_y, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//		}
//	}
//	
//	for(x = 4; 0 <= x; x--){
//			lcd_print_stringXY(win, x, win_screen_y, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
//		if( x > 2 ){ 
//			lcd_print_stringXY(win, x-1, win_screen_y, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//		}
//	}

//}

//void print_lose() {
//	char win[] = "YOU LOST!!";
//	
//	int8_t x = 0; 
//	
//	lcd_clear_screen(LCD_COLOR_BLACK);
//	
//	for(x = 0; x <= 4; x++){
//			lcd_print_stringXY(win, x, win_screen_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
//		if( x <4){ 
//			lcd_print_stringXY(win, x-1, win_screen_y, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//		}
//	}
//	
//	for(x = 4; 0 <= x; x--){
//			lcd_print_stringXY(win, x, win_screen_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
//		if( x > 2 ){ 
//			lcd_print_stringXY(win, x-1, win_screen_y, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//		}
//	}
//}

void win_screen() {
	
	char your_score[] = "YOUR SCORE: ";
	char high_score[] = "HIGH SCORE: ";
	char new_score[] = "NEW HIGH";
	char h_score[] = "SCORE: ";
	
	char player_score_arr[4] = "000"; // ADD THE CURRENT PLAYER'S SCORE
	char high_score_arr[4] = "000"; 
	char new_high_score[4] = "000";
	
	// clear screen
	lcd_clear_screen(LCD_COLOR_BLACK);
	
	
	// image creation
	
				lcd_draw_image(
                  55,            		  // X Pos
                  winWidthPixels, 		// Image Horizontal Width
                  150,       				  // Y Pos
                  winHeightPixels,		// Image Vertical Height
                  winBitmaps, 				// Image
                  LCD_COLOR_GREEN,    // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
								
		// printing to screens
		lcd_print_stringXY(your_score, your_score_x, your_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		// PRINT LINE FOR PLAYER'S SCORE *ACTUAL SCORE* player_score_arr
		lcd_print_stringXY(player_score_arr,your_score_x + 11,your_score_y, LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
	
		lcd_print_stringXY(high_score, high_score_x, high_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		// PRINT LINE FOR HIGH SCORE *ACTUAL SCORE* high_score_arr
		lcd_print_stringXY(high_score_arr, high_score_x + 11, high_score_y, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
		
		lcd_print_stringXY(new_score, new_score_x, new_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		lcd_print_stringXY(h_score, h_score_x, h_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		// PRINT LINE FOR NEW HIGH SCORE *ACTUAL SCORE* new_high_score
		lcd_print_stringXY(new_high_score, h_score_x + 11, h_score_y, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
}

void lose_screen() {
	
	char your_score[] = "YOUR SCORE: ";
	char high_score[] = "HIGH SCORE: ";
	char new_score[] = "NEW HIGH";
	char h_score[] = "SCORE: ";
	
	char player_score_arr[4] = "000"; // ADD THE CURRENT PLAYER'S SCORE
	char high_score_arr[4] = "000"; 
	char new_high_score[4] = "000";
	
	// clear screen
	lcd_clear_screen(LCD_COLOR_BLACK);
	
	
	// image creation
	
				lcd_draw_image(
                  55,            		  // X Pos
                  lOSEBITMAPWidthPixels, 		// Image Horizontal Width
                  150,       				  // Y Pos
                  lOSEBITMAPHeightPixels,		// Image Vertical Height
                  lOSEBITMAPBitmaps, 				// Image
                  LCD_COLOR_RED,    // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
								
		// printing to screens
		lcd_print_stringXY(your_score, your_score_x, your_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		// PRINT LINE FOR PLAYER'S SCORE *ACTUAL SCORE* player_score_arr
		lcd_print_stringXY(player_score_arr,your_score_x + 11,your_score_y, LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
	
		lcd_print_stringXY(high_score, high_score_x, high_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		// PRINT LINE FOR HIGH SCORE *ACTUAL SCORE* high_score_arr
		lcd_print_stringXY(high_score_arr, high_score_x + 11, high_score_y, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
		
		lcd_print_stringXY(new_score, new_score_x, new_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		lcd_print_stringXY(h_score, h_score_x, h_score_y, LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		// PRINT LINE FOR NEW HIGH SCORE *ACTUAL SCORE* new_high_score
		lcd_print_stringXY(new_high_score, h_score_x + 11, h_score_y, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
	
	
}

//void print_end_screen() {
//	
//	char dot[] = "--------------";
//	
//	char msg1[] = "PLAY AGAIN";
//	char msg2[] = "HIGH SCORES";
//	
//	// clear screen 
//	lcd_clear_screen(LCD_COLOR_BLACK);
//	
//	// prints messages 1 and 2 with MACROS
//	lcd_print_stringXY(msg1,end_screen_play_x,end_screen_play_y, LCD_COLOR_GREEN,LCD_COLOR_BLACK);
//  lcd_print_stringXY(msg2,end_screen_high_x,end_screen_high_y, LCD_COLOR_RED,LCD_COLOR_BLACK);
//	
//	// 4 lines below for drawing the boxes, WITH MACROS
//	lcd_print_stringXY(dot, draw_line_x, (end_screen_play_y - offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
//	lcd_print_stringXY(dot, draw_line_x, (end_screen_play_y + offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
//	
//	lcd_print_stringXY(dot, draw_line_x, (end_screen_high_y - offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
//	lcd_print_stringXY(dot, draw_line_x, (end_screen_high_y + offset), LCD_COLOR_BLUE, LCD_COLOR_BLACK);
//}

void pause_screen() {
	uint8_t touch_event;
	uint16_t x,y;
	
	x = ft6x06_read_x();
	y = ft6x06_read_y();
	
  printf("Touch Events :\tX: %d\t||\tY: %d \n\r", x, y);
	print_pause_screen();
				
}
