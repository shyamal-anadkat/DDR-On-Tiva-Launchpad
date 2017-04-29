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

#define SEC_ONE     50000000
#define WAIT_TIME   500000
#define ONE_SHOT    TIMER_TAMR_TAMR_1_SHOT
#define PERIODIC    TIMER_TAMR_TAMR_PERIOD
#define ARROW_DELAY 10000


// DIFFICULTY MODE - ANIMATION SPEEDS
#define DIFFICULTY_TIMER_EASY		3
#define DIFFICULTY_TIMER_MEDIUM	2
#define DIFFICULTY_TIMER_HARD		8




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

#endif