#include "ddr_game.h"

uint16_t score; 
uint8_t consecutive_boos;
uint8_t consecutive_misses;
uint8_t consecutive_goods;

uint8_t random_ticks;
extern uint8_t led_blink_ticks;

void add_random_arrow(void) {
	static uint8_t time = 0;
	static uint8_t arrow_dir;
	arrow_dir_t dir;
	
	if(random_ticks == 0) {
		random_ticks = rand();
		if(random_ticks < 50) {
			random_ticks *= 5;
		}
		dir = convert_int_to_arrow(random_ticks % 4);
		add_arrow(dir);
		printf("random_ticks: %d\n", random_ticks);
	}
	else {
		random_ticks--;	
	}
}


void change_LED_expander_state(print_type_t print_type) {
	led_blink_ticks++;
	
	switch(print_type) {
		case NONE:
			return;
		case GOOD:
			handle_good();
		case BOO:
			handle_boo_miss();
		case MISS:
			handle_boo_miss();
	}
}

void handle_good(void) {
	if (consecutive_goods >= 2) {
		io_expander_blink_state(RAISE);
		consecutive_goods = 0;
	} 
	else {
		consecutive_goods++;
	}
}

void handle_boo_miss(void) {
		if (consecutive_boos >= 2 || consecutive_misses >= 2) {
		io_expander_blink_state(DROP); 
		consecutive_boos = 0;
		consecutive_misses = 0;
	} 
	else {
		consecutive_boos++;
		consecutive_misses++;
	}
}