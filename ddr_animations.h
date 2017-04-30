#ifndef __DDR_ANIMATIONS_H__
#define __DDR_ANIMATIONS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "serial_debug.h"
#include "lcd.h"
#include "ddr_images.h"
#include "timers.h"
#include "mcp23017.h"
#include "arrow.h"
#include "arrow_printing.h"
#include "menu_nav.h"
#include "io_expander_led.h"

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
// ARROW QUEUE
//*****************************************************************************

#define NULL_VALUE	0

typedef struct QNode {
	arrow_t *key;
	struct QNode *next;
} queue_node;

typedef struct queue {
	queue_node *head;
	queue_node *tail;
} queue_t;

void init_arrow_queue(void);
queue_node *new_node(arrow_t *arrow);
queue_t *create_queue(void);
void enqueue(queue_t *queue, arrow_t *arrow);
queue_node *dequeue(queue_t *queue);


//*****************************************************************************
// ARROW FUNCTIONALITY
//*****************************************************************************

bool add_arrow(arrow_dir_t dir);
bool add_two_arrows(arrow_dir_t dir1, arrow_dir_t dir2);
void animate_arrows(uint8_t button_val);


//*****************************************************************************
// PLAY MODE ANIMATIONS
//*****************************************************************************

void update_ui_init_play(void);
void init_play_top_arrows(void);
void update_ui_play(uint8_t button_data);

void update_ui_init_high_score(void);

void arrow_delay(void);
void print_score(void);

void clear_print_message(void);


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