#ifndef __MENU_NAV_H__
#define __MENU_NAV_H__

#include "lcd.h"
#include "ddr_images.h"
#include "ddr_animations.h"

#define x_left_threshold  (0xFFF / 4) * 3
#define y_up_threshold  	(0xFFF / 4) * 3
#define x_right_threshold (0xFFF / 4)
#define y_down_threshold  (0xFFF / 4)


typedef enum {
	NOTHING,
	PLAY_NOW,
	HIGH_SCORES
} SELECTED_ITEM;

typedef enum {
	MENU, PLAY, WIN, LOSE
} game_state_fsm;

void display_selected_menu_item();
void navigate_main_menu(uint16_t y_adc_data);
void update_ui_init_new_state(game_state_fsm new_state);

void update_ui_init_main_menu(void);
void draw_line(uint8_t y);
void clear_line(uint8_t y);

#endif