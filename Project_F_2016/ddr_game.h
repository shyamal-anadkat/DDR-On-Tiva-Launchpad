#ifndef __DDR_GAME_H__
#define __DDR_GAME_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "serial_debug.h"
#include "ddr_animations.h"


#define MAX_INTERVAL_EASY 141
#define MIN_INTERVAL_EASY 40
#define MAX_INTERVAL_MEDIUM 81
#define MIN_INTERVAL_MEDIUM 50
#define MAX_INTERVAL_HARD 31
#define MIN_INTERVAL_HARD 10

// DIFFICULTY MODE - ANIMATION SPEEDS
#define DIFFICULTY_MODE_EASY 		1
#define DIFFICULTY_MODE_MEDIUM 	2
#define DIFFICULTY_MODE_HARD 		3
#define MAX_ARROWS_EASY   			15
#define MAX_ARROWS_MEDIUM 			30
#define MAX_ARROWS_HARD   			60

#define MAX_SCORE_POSSIBLE			(MAX_ARROWS_HARD * SCORE_PER_ARROW)

#define SCORE_PER_ARROW					10

void change_LED_expander_state(print_type_t);
void add_random_arrow(void);
void change_LED_expander_state(print_type_t);
void add_random_arrow(void);
void handle_good(void);
void handle_boo(void);
void handle_miss(void);

#endif