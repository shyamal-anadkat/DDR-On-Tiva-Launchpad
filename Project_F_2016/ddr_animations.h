#ifndef __DDR_ANIMATIONS_H__
#define __DDR_ANIMATIONS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "serial_debug.h"
#include "lcd.h"
#include "ddr_images.h"
#include "ddr_game.h"
#include "timers.h"


#define SEC_ONE     50000000
#define WAIT_TIME   500000
#define ONE_SHOT    TIMER_TAMR_TAMR_1_SHOT


typedef enum {ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT} arrow_dir_t;

// Defines an arrow that will be placed on the screen.
// Assumes bitmaps for each arrow type are stored elsewhere
// Assumes x coordinates for each arrow type are stored elsewhere
typedef struct{
	arrow_dir_t arrow_type;
	uint16_t y_pos;
}arrow_t;



void print_arrow(arrow_t arrow);
bool add_arrow(arrow_dir_t dir);
bool add_two_arrows(arrow_dir_t dir1, arrow_dir_t dir2);
void animate_arrows(void);

#endif