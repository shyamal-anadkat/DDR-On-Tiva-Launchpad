#ifndef __DDR_GAME_H__
#define __DDR_GAME_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "serial_debug.h"

//
//	DECLARE CONSTANTS
//
#define ARROW_POS_START_Y				5
#define ARROW_POS_END_Y 			275
#define ARROW_POS_X_UP				105
#define ARROW_POS_X_DOWN			150
#define ARROW_POS_X_LEFT			195
#define ARROW_POS_X_RIGHT			 60
#define ARROW_WIDTH						 40
#define ARROW_HEIGHT					 39
#define MAX_ARROWS_ON_SCREEN 	 25


typedef enum {
	MENU, PLAYING, WIN, LOSE
} game_state;


typedef enum {ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT} arrow_dir_t;

// Defines an arrow that will be placed on the screen.
// Assumes bitmaps for each arrow type are stored elsewhere
// Assumes x coordinates for each arrow type are stored elsewhere
typedef struct{
	arrow_dir_t arrow_type;
	uint16_t y_pos;
}arrow_t;







#endif