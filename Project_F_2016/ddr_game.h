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
#define MAX_INTERVAL_HARD 61
#define MIN_INTERVAL_HARD 20

void change_LED_expander_state(print_type_t);
void add_random_arrow(void);


#endif