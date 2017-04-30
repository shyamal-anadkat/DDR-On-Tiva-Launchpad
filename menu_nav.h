#ifndef __MENU_NAV_H__
#define __MENU_NAV_H__


#include "ddr_animations.h"
#include "ft6x06.h"
#include "lcd.h"
#include "ddr_images.h"

#define x_left_threshold  (0xFFF / 4) * 3
#define y_up_threshold  	(0xFFF / 4) * 3
#define x_right_threshold (0xFFF / 4)
#define y_down_threshold  (0xFFF / 4)

#define PRINT_MESSAGE_DELAY 300

// offset macro
#define offset 1

// x is zero for drawing boxes
#define draw_line_x 0 

// macros for main menu
#define menu_play_now_x 2
#define menu_play_now_y 2
#define menu_high_scores_x 1
#define menu_high_scores_y 4

//hit, miss, boo screen macros
#define hit_screen_x 10
#define hit_screen_y 10

#define miss_screen_x 10
#define miss_screen_y 10

#define boo_screen_x 10
#define boo_screen_y 10

//printing pause screen 
#define pause_screen_continue_x 3
#define pause_screen_continue_y 5

#define pause_screen_menu_x 5
#define pause_screen_menu_y 10

//printing end screen 
#define end_screen_play_x 2
#define end_screen_play_y 5

#define end_screen_high_x 2
#define end_screen_high_y 10 

//macros for high scores screen
#define high_screen_x 0
#define high_screen_y 4

#define score_screen_x 0
#define score_screen_y 5

#define longest_screen_x 0
#define longest_screen_y 7

#define time_screen_x 0
#define time_screen_y 8

#define game_screen_x 0
#define game_screen_y 10

#define mode_screen_x 0
#define mode_screen_y 11

#define back_screen_x 5
#define back_screen_y 18

// macros for win screen 
#define win_screen_x  0
#define win_screen_y 10 

typedef enum {
	NOTHING,
	PLAY_NOW,
	HIGH_SCORES
} SELECTED_ITEM;

typedef enum {
	MENU, PLAY, WIN, LOSE, HIGH_SCORE
} game_state_fsm;

void display_selected_menu_item();
void navigate_main_menu(uint16_t y_adc_data);
void update_ui_init_new_state(game_state_fsm new_state);

void update_ui_init_main_menu(void);
void draw_line(uint8_t y);
void clear_line(uint8_t y);

void print_hit_second(void);
void print_boo_second(void);
void print_miss_second(void);

void clear_hit(void);
void clear_boo(void);

void print_pause_screen(void);
void print_end_screen(void);

void print_high_scores(void);
void print_lose(void);
void print_win(void);
#endif