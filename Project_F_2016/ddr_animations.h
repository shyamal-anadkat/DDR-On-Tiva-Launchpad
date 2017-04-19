#ifndef __DDR_ANIMATIONS_H__
#define __DDR_ANIMATIONS_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "serial_debug.h"
#include "lcd.h"
#include "ece353_images.h"

#define SEC_ONE     50000000
#define WAIT_TIME   500000
#define ONE_SHOT    TIMER_TAMR_TAMR_1_SHOT

void print_arrows(void);
void display_welcome_screen(void);
void move_arrows(int num, int dir, int speed, uint16_t fColor, uint16_t bColor);

#endif