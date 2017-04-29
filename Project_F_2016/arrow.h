#ifndef __ARROW_H__
#define __ARROW_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>


//*****************************************************************************
// ARROW CONSTANTS AND FUNCTIONALITY
//*****************************************************************************
#define ARROW_POS_START_Y					5
#define ARROW_POS_END_Y 				319
#define ARROW_POS_TRGT_Y				250 // bottom of arrow
#define	ARROW_POS_TRGT_TOP_Y		ARROW_POS_TRGT_Y + ARROW_HEIGHT
#define ARROW_POS_X_UP					105
#define ARROW_POS_X_DOWN				150
#define ARROW_POS_X_LEFT				195
#define ARROW_POS_X_RIGHT				 60
#define ARROW_WIDTH							 40
#define ARROW_HEIGHT						 39

#define ARROW_TOP_COLOR_UP			LCD_COLOR_CYAN
#define ARROW_TOP_COLOR_DOWN		LCD_COLOR_ORANGE
#define ARROW_TOP_COLOR_LEFT		LCD_COLOR_RED
#define ARROW_TOP_COLOR_RIGHT		LCD_COLOR_YELLOW


typedef enum {ARROW_DIR_UP, ARROW_DIR_DOWN, ARROW_DIR_LEFT, ARROW_DIR_RIGHT} arrow_dir_t;
// Defines an arrow that will be placed on the screen.
// Assumes bitmaps for each arrow type are stored elsewhere
// Assumes x coordinates for each arrow type are stored elsewhere


typedef struct{
	arrow_dir_t arrow_type;
	uint16_t y_pos;
	uint16_t color; // LCD_COLOR MACROS
}arrow_t;

arrow_dir_t convert_int_to_arrow(uint16_t);

#endif