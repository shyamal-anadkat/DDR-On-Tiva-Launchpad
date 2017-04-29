#ifndef __ARROW_PRINTING_H__
#define __ARROW_PRINTING_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "arrow.h"
#include "lcd.h"

//*****************************************************************************
// ARROW REGION CONSTANTS
//*****************************************************************************
#define 	RGN_GOOD	20
#define 	RGN_BAD		40
#define		RGN_MISS	ARROW_POS_END_Y // top of LCD
#define		RGN_BOO		60
#define		RGN_NONE	80


void print_arrow(arrow_t *arrow);
void clear_arrow(arrow_t *arrow);
void print_top_arrow(arrow_dir_t arrow_dir);

typedef enum {
	NONE, GOOD, BAD, MISS, BOO
} print_type_t;

#endif