#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "driver_defines.h"
#include "gpio_port.h"
#include "i2c.h"
#include "timers.h"

#define LED7 0x80
#define LED6 0x40
#define LED5 0x20
#define LED4 0x10
#define LED3 0x08
#define LED2 0x04
#define LED1 0x02
#define LED0 0x01
#define NOT_LED  0x00

#define FAST_BLINK  70
#define MEDIUM_BLINK 100
#define SLOW_BLINK 130

void control_leds(uint8_t data);

typedef enum {
	FAST,
	MEDIUM,
	SLOW,
	DROP
} led_blink_rate;


