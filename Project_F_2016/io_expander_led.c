#include "io_expander_led.h"

// function for change in blinking of IO expander LEDs based on different states.
// if the state is fast, blink the LED fast
// medium = medium speed
// slow = slow speed

led_blink_rate_t blink_rate = FAST;
uint8_t led_blink_ticks = 0;
static uint8_t active_led_num = 7;

void io_expander_blink_state(led_blink_rate_t new_rate) {	
	
	switch(new_rate) {
		case RAISE:
			active_led_num++;
			blink_rate = SLOW;
			led_blink();
			break;
 		case FAST:
			if(led_blink_ticks == BLINK_FAST) led_blink();
			break;
		case MEDIUM:
			if(led_blink_ticks == BLINK_FAST) led_blink();
			break;
		case SLOW:
			if(led_blink_ticks == BLINK_FAST) led_blink();
			break;
		case DROP:
			active_led_num--;
			blink_rate = FAST;
			led_blink();
			break;
	}
}

void led_blink(void) {
	// Blink on if true, off if false
	(led_blink_ticks % 2 == 0) ? handle_led_blink(true) : handle_led_blink(false);
}

void handle_led_blink(bool on) {
	switch(active_led_num) {
		case 0:
			(on) ? control_leds(IO_EXP_LED0 | IO_EXP_LED0_M) : control_leds(~IO_EXP_LED0 | IO_EXP_LED0_M);
			break;
		case 1:
			(on) ? control_leds(IO_EXP_LED1 | IO_EXP_LED1_M) : control_leds(~IO_EXP_LED1 | IO_EXP_LED1_M);
			break;
		case 2:
		(on) ? control_leds(IO_EXP_LED2 | IO_EXP_LED2_M) : control_leds(~IO_EXP_LED2 | IO_EXP_LED2_M);
			break;
		case 3: 
		(on) ? control_leds(IO_EXP_LED3 | IO_EXP_LED3_M) : control_leds(~IO_EXP_LED3 | IO_EXP_LED3_M);
			break;
		case 4:
		(on) ? control_leds(IO_EXP_LED4 | IO_EXP_LED4_M) : control_leds(~IO_EXP_LED4 | IO_EXP_LED4_M);
			break;
		case 5:
		(on) ? control_leds(IO_EXP_LED5 | IO_EXP_LED5_M) : control_leds(~IO_EXP_LED5 | IO_EXP_LED5_M);
			break;
		case 6:
			(on) ? control_leds(IO_EXP_LED6 | IO_EXP_LED6_M) : control_leds(~IO_EXP_LED6 | IO_EXP_LED6_M);
			break;
		case 7:
		(on) ? control_leds(IO_EXP_LED7 | IO_EXP_LED7_M) : control_leds(~IO_EXP_LED7 | IO_EXP_LED7_M);
			break;
	}
}