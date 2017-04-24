#ifndef __DDR_GAME_H__
#define __DDR_GAME_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "serial_debug.h"
#include "ddr_animations.h"

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
	MENU, PLAY, WIN, LOSE
} game_state_fsm;




void update_ui_init_play(void);
void update_ui_play(void);





#endif