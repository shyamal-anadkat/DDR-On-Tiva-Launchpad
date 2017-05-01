#include "io_expander_led.h"

// function for change in blinking of IO expander LEDs based on different states.
// if the state is fast, blink the LED fast
// medium = medium speed
// slow = slow speed

led_blink_rate_t blink_rate = FAST;
uint8_t led_blink_ticks = 0;
uint8_t active_led_num = 7;

void io_expander_blink_state(led_blink_rate_t new_rate) {	
	
	switch(new_rate) {
		case RAISE:
			blink_rate = raise_blink_rate(blink_rate);
			led_blink(false);
			break;
 		case FAST:
			(led_blink_ticks % BLINK_FAST <= (BLINK_FAST / 2)) ? led_blink(true) : led_blink(false);
			break;
		case MEDIUM:
			(led_blink_ticks % BLINK_MEDIUM <= (BLINK_MEDIUM / 2)) ? led_blink(true) : led_blink(false);
			break;
		case SLOW:
			(led_blink_ticks % BLINK_SLOW <= (BLINK_SLOW / 2)) ? led_blink(true) : led_blink(false);
			break;
		case DROP:
			blink_rate = drop_blink_rate(blink_rate);
			led_blink(false);
			break;
	}
	
	led_blink_ticks = (led_blink_ticks > UINT8_MAX_VAL) ? 0 : ++led_blink_ticks;

}

led_blink_rate_t raise_blink_rate(led_blink_rate_t curr_blink_rate) {
	switch (curr_blink_rate){
		case FAST:
			active_led_num = (++active_led_num > 7) ? 7 : active_led_num;
			return (active_led_num == 7) ? FAST : SLOW;
		case MEDIUM:
			return FAST;
		case SLOW:
			return MEDIUM;
		default:
			return MEDIUM; // SHOULD NEVER GET HERE
	}
}

led_blink_rate_t drop_blink_rate(led_blink_rate_t curr_blink_rate) {
	switch (curr_blink_rate){
		case FAST:
			return MEDIUM;
		case MEDIUM:
			return SLOW;
		case SLOW:
			active_led_num = (--active_led_num < 0) ? 0 : active_led_num;
			return FAST;
		default:
			return MEDIUM; // SHOULD NEVER GET HERE
	}
}

void led_blink(bool blink) {
	// Blink on if true, off if false
	//(led_blink_ticks % 2 == 0) ? handle_led_blink(true) : handle_led_blink(false);
	handle_led_blink(blink);
}

void handle_led_blink(bool on) {
	switch(active_led_num) {
		case 0:
			(on) ? control_leds(IO_EXP_LED0 | IO_EXP_LED0_M) : control_leds(~IO_EXP_LED0 & IO_EXP_LED0_M);
			break;
		case 1:
			(on) ? control_leds(IO_EXP_LED1 | IO_EXP_LED1_M) : control_leds(~IO_EXP_LED1 & IO_EXP_LED1_M);
			break;
		case 2:
		(on) ? control_leds(IO_EXP_LED2 | IO_EXP_LED2_M) : control_leds(~IO_EXP_LED2 & IO_EXP_LED2_M);
			break;
		case 3: 
		(on) ? control_leds(IO_EXP_LED3 | IO_EXP_LED3_M) : control_leds(~IO_EXP_LED3 & IO_EXP_LED3_M);
			break;
		case 4:
		(on) ? control_leds(IO_EXP_LED4 | IO_EXP_LED4_M) : control_leds(~IO_EXP_LED4 & IO_EXP_LED4_M);
			break;
		case 5:
		(on) ? control_leds(IO_EXP_LED5 | IO_EXP_LED5_M) : control_leds(~IO_EXP_LED5 & IO_EXP_LED5_M);
			break;
		case 6:
			(on) ? control_leds(IO_EXP_LED6 | IO_EXP_LED6_M) : control_leds(~IO_EXP_LED6 & IO_EXP_LED6_M);
			break;
		case 7:
		(on) ? control_leds(IO_EXP_LED7 | IO_EXP_LED7_M) : control_leds(~IO_EXP_LED7 & IO_EXP_LED7_M);
			break;
	}
}