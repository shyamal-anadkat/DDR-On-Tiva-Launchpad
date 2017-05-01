#ifndef __ARROW_PRINTING_H__
#define __ARROW_PRINTING_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "arrow.h"
#include "lcd.h"

//*****************************************************************************
// ARROW REGION CONSTANTS (IN HEX !!!)
//*****************************************************************************
#define 	RGN_GOOD	0x24
#define		RGN_MISS	ARROW_POS_END_Y // top of LCD
#define		RGN_BOO		0xd0
#define		RGN_NONE	0xf0

#define PRINT_MESSAGE_DELAY 75


void print_arrow(arrow_t *arrow);
void clear_arrow(arrow_t *arrow);
void print_top_arrow(arrow_dir_t arrow_dir);
void print_top_arrow_hit(arrow_dir_t arrow_dir);

typedef enum {
	NONE, GOOD, BAD, MISS, BOO
} print_type_t;

void clear_hit_miss_message(void);

void print_hit_second(void);
void print_boo_second(void);
void print_miss_second(void);

void clear_hit(void);
void clear_boo(void);

#endif