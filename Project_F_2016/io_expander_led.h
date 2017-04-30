#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "driver_defines.h"
#include "gpio_port.h"
#include "i2c.h"
#include "timers.h"
#include "mcp23017.h"

#define IO_EXP_LED7 			0x80
#define IO_EXP_LED6 			0x40
#define IO_EXP_LED5 			0x20
#define IO_EXP_LED4 			0x10
#define IO_EXP_LED3 			0x08
#define IO_EXP_LED2 			0x04
#define IO_EXP_LED1 			0x02
#define IO_EXP_LED0 			0x01
#define IO_EXP_LED_NONE	0x00

#define IO_EXP_LED7_M		0xFF
#define IO_EXP_LED6_M		0x7F
#define IO_EXP_LED5_M		0x3F
#define IO_EXP_LED4_M		0x1F
#define IO_EXP_LED3_M		0x0F
#define IO_EXP_LED2_M		0x07
#define IO_EXP_LED1_M		0x03
#define IO_EXP_LED0_M		0x01

#define BLINK_FAST  20//70
#define BLINK_MEDIUM 40//100
#define BLINK_SLOW 60//130

typedef enum {
	RAISE,
	FAST,
	MEDIUM,
	SLOW,
	DROP
} led_blink_rate_t;

void control_leds(uint8_t data);
void io_expander_blink_state(led_blink_rate_t new_rate);
void led_blink(void);
void handle_led_blink(bool);
