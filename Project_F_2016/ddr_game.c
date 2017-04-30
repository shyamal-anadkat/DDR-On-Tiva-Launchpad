#include "ddr_game.h"

uint16_t score = 0; 
uint8_t boos_in_a_row;
uint8_t misses_in_a_row;
uint8_t goods_in_a_row;

uint8_t random_ticks;

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


//void change_LED_expander_state(print_type_t print_type) {
//	switch(print_type) {
//		case NONE:
//			return;
//		case GOOD:
//			handle_good();
//		case BOO:
//			handle_boo();
//		case MISS:
//			handle_miss();
//	}
//}

//void handle_good(void) {
//	
//}