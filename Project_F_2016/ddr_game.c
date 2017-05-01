#include "ddr_game.h"

uint16_t score = 0; 
uint8_t boos_in_a_row;
uint8_t misses_in_a_row;
uint8_t goods_in_a_row;
uint8_t random_ticks;

extern uint8_t GAME_MODE;
extern uint8_t enqueued_arrows;
extern uint8_t max_arrows;

void add_random_arrow(void) {
	static uint8_t time = 0;
	static uint8_t arrow_dir;
	arrow_dir_t dir;
	
	if(enqueued_arrows > max_arrows) return;
	
	if(random_ticks == 0) {
		random_ticks = rand();

		
		switch(GAME_MODE) {
			case DIFFICULTY_MODE_EASY: 
				random_ticks = rand() % MAX_INTERVAL_EASY + MIN_INTERVAL_EASY;
				break;
			case DIFFICULTY_MODE_MEDIUM:
				random_ticks = rand() % MAX_INTERVAL_MEDIUM + MIN_INTERVAL_MEDIUM;
				break;
			case DIFFICULTY_MODE_HARD:
				random_ticks = rand() % MAX_INTERVAL_HARD + MIN_INTERVAL_HARD;
				break;
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
	
	switch(print_type) {
		case NONE:
			break;
		case GOOD:
			handle_good();
			break;
		case BOO:
			handle_boo();
			break;
		case MISS:
			handle_miss();
			break;
	}
}

void handle_good(void) {
	io_expander_blink_state(RAISE);
}

void handle_boo(void) {
	io_expander_blink_state(DROP);
}

void handle_miss(void) {
	io_expander_blink_state(DROP);
	io_expander_blink_state(DROP);
}