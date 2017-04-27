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

#define SEC_ONE     50000000
#define WAIT_TIME   500000
#define ONE_SHOT    TIMER_TAMR_TAMR_1_SHOT
#define PERIODIC    TIMER_TAMR_TAMR_PERIOD


// DIFFICULTY MODE - ANIMATION SPEEDS
#define DIFFICULTY_TIMER_EASY		3
#define DIFFICULTY_TIMER_MEDIUM	2
#define DIFFICULTY_TIMER_HARD		1


//*****************************************************************************
// ARROW CONSTANTS AND FUNCTIONALITY
//*****************************************************************************
#define ARROW_POS_START_Y				5
#define ARROW_POS_END_Y 			275
#define ARROW_POS_TRGT_Y			250
#define ARROW_POS_X_UP				105
#define ARROW_POS_X_DOWN			150
#define ARROW_POS_X_LEFT			195
#define ARROW_POS_X_RIGHT			 60
#define ARROW_WIDTH						 40
#define ARROW_HEIGHT					 39

typedef enum {ARROW_DIR_UP, ARROW_DIR_DOWN, ARROW_DIR_LEFT, ARROW_DIR_RIGHT} arrow_dir_t;
typedef enum {
	EXCELLENT, GOOD, OK, BAD, 
} arrow_rgn_t;


// Defines an arrow that will be placed on the screen.
// Assumes bitmaps for each arrow type are stored elsewhere
// Assumes x coordinates for each arrow type are stored elsewhere
typedef struct{
	arrow_dir_t arrow_type;
	uint16_t y_pos;
	uint16_t color; // LCD_COLOR MACROS
}arrow_t;



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

void print_arrow(arrow_t arrow);
bool add_arrow(arrow_dir_t dir);
bool add_two_arrows(arrow_dir_t dir1, arrow_dir_t dir2);
void animate_arrows();



//*****************************************************************************
// PLAY MODE ANIMATIONS
//*****************************************************************************

void update_ui_init_play(void);
void init_play_top_arrows(void);
void update_ui_play(uint8_t button_data);




#endif