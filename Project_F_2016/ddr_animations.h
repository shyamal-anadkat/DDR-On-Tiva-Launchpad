#ifndef __DDR_ANIMATIONS_H__
#define __DDR_ANIMATIONS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "serial_debug.h"
#include "lcd.h"
#include "ddr_images.h"
#include "timers.h"
#include "mcp23017.h"
#include "arrow.h"
#include "arrow_printing.h"
#include "menu_nav.h"
#include "io_expander_led.h"
#include "arrow_queue.h"
#include "ddr_game.h"
#include "eeprom.h"

#define SEC_ONE     50000000
#define WAIT_TIME   500000
#define ONE_SHOT    TIMER_TAMR_TAMR_1_SHOT
#define PERIODIC    TIMER_TAMR_TAMR_PERIOD
#define DELAY_FLASH 			40

#define LED_LEVEL_8 0xFF
#define LED_LEVEL_7 0x7F
#define LED_LEVEL_6 0x3F
#define LED_LEVEL_5 0x1F
#define LED_LEVEL_4 0x0F
#define LED_LEVEL_3 0x07
#define LED_LEVEL_2 0x03
#define LED_LEVEL_1 0x01
#define LED_LEVEL_0 0x00

// macros for touch screen for win lose

#define play_again_upper_bound 235
#define play_again_lower_bound 208

#define high_scores_upper_bound 150
#define high_scores_lower_bound 128

// macros for high score
#define back_upper_bound 38
#define back_lower_bound 2

// macros for pause
#define continue_upper_bound 235
#define continue_lower_bound 208

#define menu_upper_bound 160
#define menu_lower_bound 128

//*****************************************************************************
// ARROW FUNCTIONALITY
//*****************************************************************************

void animate_arrows(uint8_t button_val);


//*****************************************************************************
// PLAY MODE ANIMATIONS
//*****************************************************************************
void update_ui_init_play(void);
void init_play_top_arrows(void);
void update_ui_play(uint8_t button_data);

void arrow_delay(void);
void print_score(void);

void update_ui_init_high_score(void);

void handle_pause_screen(void);
void handle_game_end(void);

uint8_t led_level(uint8_t level);

//*****************************************************************************
// PROCESS ARROW FUNCTIONALITY
//*****************************************************************************

// PROCESSES THE FIRST ARROW IN THE QUEUE
// THIS FUNCTION WILL REMOVE THE FIRST ARROW IF IT IS IN A VALID REGION
// *** AND WILL MOVE THE 
print_type_t process_arrow(arrow_t *arrow, uint8_t button_val);

// returns the new head node before continuing updating arrows
bool correct_button_pressed(arrow_t * arrow, uint8_t button_val);
print_type_t determine_button_outcome(uint16_t difference, uint16_t arrow_y_pos_top);
queue_node *process_print(print_type_t print_type);

void print_pause_button();


// PROCESS PRINT HANDLING FUNCTIONS
void process_print_good(arrow_t *arrow);
void process_print_miss(arrow_t *arrow);

#endif