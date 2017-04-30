#include "ddr_animations.h"

extern queue_t *queue;

extern bool Alert_Timer0A;
extern bool Alert_Timer0B;
extern uint16_t score;

static bool is_arrow_green = false;
static arrow_t *last_arrow_hit;


//*****************************************************************************
//
// PLAY MODE ANIMATIONS
//
//*****************************************************************************

//*****************************************************************************
// Initializes the UI for PLAY mode
//*****************************************************************************
void update_ui_init_play(void) {
	uint16_t timer_val = get_timer0A_current_value();
 	uint16_t i = 0;
	lcd_clear_screen(LCD_COLOR_BLACK);
	init_play_top_arrows();
	score = 0; 
		
	srand(timer_val); // TODO: This might be bad to call multiple times

}

//*****************************************************************************
// Updates the entire user interface of the game in PLAY mode
// Increments all of the onscreen arrows by 1	
//*****************************************************************************
void update_ui_play(button_dir_t button_data) {
	// need button to be stateful so it can be handled when timer goes off
	static button_dir_t button_val = BTN_NONE; 
	static uint16_t ticks = 0;

	
	// handle glitchy '2' that appears in button data before correct value appears
	if(button_data != BTN_NONE && button_data != 2) {
		button_val = button_data;
	}
	
	
	if(Alert_Timer0A) {
		
		print_score();
		animate_arrows(button_val);
		add_random_arrow();
		button_val = BTN_NONE; // after processing the button value, reset it to NONE
		
		// To handle the green flash on hit 
		ticks++;
		if(ticks > DELAY_FLASH) {ticks = 0;}
		if((ticks == DELAY_FLASH) && (is_arrow_green == true)){
			print_top_arrow(last_arrow_hit->arrow_type);
			is_arrow_green = false;
			ticks = 0;
		}
		Alert_Timer0A = false;
	}
	
	//clear miss/hit message on LCD
	clear_hit_miss_message();
	//led_blink(FAST);
}


void animate_arrows(uint8_t button_val) {	
	print_type_t print_type;
	queue_node *curr_node = queue->head;
	
	arrow_t *arrow = curr_node->key;

	// nothing to animate if the queue is empty!
	if(queue->head == NULL_VALUE) return;
	
	// evaluate arrow position and button values together
	print_type = process_arrow(arrow, button_val);
	
	// process print returns new head node, function itself handles outcome of button press
	curr_node = process_print(print_type);
	// change_LED_expander_state(print_type);
	
	
	// MOVE THE REST OF THE ARROWS UP
	while(curr_node != NULL_VALUE) {
		arrow = curr_node->key;
		arrow->y_pos++;
		print_arrow(arrow);
		curr_node = curr_node->next;
	}
}


void init_play_top_arrows(void) {
	print_top_arrow(ARROW_DIR_UP);
	print_top_arrow(ARROW_DIR_DOWN);
	print_top_arrow(ARROW_DIR_LEFT);
	print_top_arrow(ARROW_DIR_RIGHT);
}



//*****************************************************************************
// ARROW PROCESSING FUNCTIONS
//*****************************************************************************
print_type_t process_arrow(arrow_t *arrow, button_dir_t button_val) {
	uint16_t y_pos_top = arrow->y_pos + ARROW_HEIGHT;
	uint16_t y_pos_trgt_top	= ARROW_POS_TRGT_TOP_Y;
	uint16_t difference;
	
	// we had to use this if-else to decide which order to subtract because they're unsigned
	// also had to use tops of each image in case the arrow went offscreen (MISS)
	difference = (y_pos_trgt_top >= y_pos_top) ? 
	(y_pos_trgt_top - y_pos_top) : (y_pos_top - y_pos_trgt_top );
	
	// printf("difference: %x\n", difference);
	// correct button, but need to see what region it was in (level of correctness)
	if (correct_button_pressed(arrow, button_val)) {
		return determine_button_outcome(difference, y_pos_top);
	} 
	
	// nothing pressed, but need to check if offscreen or just far away from target region
	else if(button_val == BTN_NONE) {
		return (y_pos_top >= ARROW_POS_END_Y) ? MISS : NONE;
	}
	
	// wrong button and on screen
	else return BOO;
}

bool correct_button_pressed(arrow_t * arrow, uint8_t button_val) {
	switch (arrow->arrow_type) {
		case ARROW_DIR_UP:
			return (button_val == BTN_U) ? true : false;
		case ARROW_DIR_DOWN:
			return (button_val == BTN_D) ? true : false;
		case ARROW_DIR_LEFT:
			return (button_val == BTN_L) ? true : false;
		case ARROW_DIR_RIGHT:
			return (button_val == BTN_R) ? true : false;
	}
}

print_type_t determine_button_outcome(uint16_t difference, uint16_t arrow_y_pos_top) {
	// miss case, goes off screen 
	if(arrow_y_pos_top >= RGN_MISS) {
		printf("MISS: %x\n", difference);
		return MISS;
	} else if (difference <= RGN_GOOD) {
		printf("GOOD: %x\n", difference);
		score += 10;
		return GOOD; 
	} else if (difference > RGN_GOOD) {
		printf("BOO: %x\n", difference);
		return BOO;
		//none region (would never come here)
	} else {
		printf("NONE: %x\n", difference);
		return NONE;
	}
}

// Returns either the first node in the queue or the next node after removing head
queue_node *process_print(print_type_t print_type) {
	arrow_t *arrow;
	
	// if NONE don't dequeue
	switch(print_type) {
		case NONE:
			//print_top_arrow_hit(arrow->arrow_type);
			break;
		case GOOD:
			print_hit_second();
			printf("process_print=good\n");
			arrow = dequeue(queue)->key;
			clear_arrow(arrow);
			print_top_arrow_hit(arrow->arrow_type);
			is_arrow_green = true; 
			last_arrow_hit = arrow;
			break;
		case MISS:
			print_miss_second();
			printf("process_print=miss\n");
			arrow = dequeue(queue)->key;
			clear_arrow(arrow);
			print_top_arrow(arrow->arrow_type);
			break;
		case BOO:
			print_boo_second();
			printf("process_print=boo\n");
			break;
		default:
			printf("process_print=default\n");
			break;
	}
	
	return queue->head;
}


