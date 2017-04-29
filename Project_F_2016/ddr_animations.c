#include "ddr_animations.h"


static queue_t *queue;
extern bool Alert_Timer0A;
extern bool Alert_Timer0B;

int score; 

void animate_arrows(uint8_t button_val) {	
	print_type_t print_type;
	queue_node *curr_node = queue->head;
	
	arrow_t *arrow = curr_node->key;

	// nothing to animate if the queue is empty!
	if(queue->head == NULL_VALUE) return;
	
	// evaluate arrow position and button values together
	print_type = process_arrow(arrow, button_val);
	
	// process print returns new head node
	curr_node = process_print(print_type);
	
	// MOVE THE REST OF THE ARROWS UP
	while(curr_node != NULL_VALUE) {
		arrow = curr_node->key;
		arrow->y_pos++;
		print_arrow(arrow);
		curr_node = curr_node->next;
	}
}


// TODO: This doesn't have to be a boolean anymore
bool add_arrow(arrow_dir_t dir) {
	arrow_t *arrow = malloc(sizeof(arrow_t));
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow->arrow_type = dir;
	arrow->y_pos = ARROW_POS_START_Y;
	arrow->color = LCD_COLOR_BLUE;
	
	enqueue(queue, arrow);
	return true;
}


bool add_two_arrows(arrow_dir_t dir1, arrow_dir_t dir2) {
	arrow_t *arrow1 = malloc(sizeof(arrow_t));
	arrow_t *arrow2 = malloc(sizeof(arrow_t));
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow1->arrow_type = dir1;
	arrow1->y_pos = ARROW_POS_START_Y;
	arrow1->color = LCD_COLOR_BLUE;

	arrow2->arrow_type = dir2;
	arrow2->y_pos = ARROW_POS_START_Y;
	arrow2->color = LCD_COLOR_BLUE;
	
	enqueue(queue, arrow1);
	enqueue(queue, arrow2);
}


//*****************************************************************************
// ARROW QUEUE
//*****************************************************************************
queue_node *new_node(arrow_t *arrow) {
	queue_node *temp = (queue_node *)malloc(sizeof(queue_node));
	temp->key = arrow;
	temp->next = NULL_VALUE;
	return temp;
}

queue_t *create_queue(void) {
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	queue->head = queue->tail = NULL_VALUE;
	return queue;
}

void enqueue(queue_t *queue, arrow_t *arrow) {
	queue_node *temp = new_node(arrow);
	if(queue->tail == NULL_VALUE) {
		queue->head = queue->tail = temp;
		return;
	}
	
	queue->tail->next = temp;
	queue->tail = temp;
}

queue_node *dequeue(queue_t *queue) {
	queue_node *temp;
	
	if(queue->head == NULL_VALUE) return NULL_VALUE;
	
	temp = queue->head;
	queue->head = queue->head->next;
	
	if(queue->head == NULL_VALUE) queue->tail = NULL_VALUE;
	
	return temp;
	
}


//*****************************************************************************
// 
//
// PLAY MODE ANIMATIONS
//
//
//*****************************************************************************

//*****************************************************************************
// Initializes the UI for PLAY mode
//*****************************************************************************
void update_ui_init_play(void) {
 	uint16_t i = 0;
	lcd_clear_screen(LCD_COLOR_BLACK);
	init_play_top_arrows();
	score = 0; 
	
	add_arrow(ARROW_DIR_UP);
	arrow_delay();
	add_arrow(ARROW_DIR_DOWN);
	arrow_delay();
	arrow_delay();
	add_arrow(ARROW_DIR_LEFT);
	arrow_delay();
	arrow_delay();
	add_arrow(ARROW_DIR_RIGHT);

}

	void arrow_delay(void) {
			if(Alert_Timer0A) {
					static int ticks = 0;
					ticks++;
					if(ticks == ARROW_DELAY){
						ticks = 0;
					}
					Alert_Timer0A = false; 
			}
			
	}

//*****************************************************************************
// Updates the entire user interface of the game in PLAY mode
// Increments all of the onscreen arrows by 1	
//*****************************************************************************
void update_ui_play(button_dir_t button_data) {
	// need button to be stateful so it can be handled when timer goes off
	static button_dir_t button_val = BTN_NONE; 
	
	// handle glitchy '2' that appears in button data before correct value appears
	if(button_data != BTN_NONE && button_data != 2) {
		button_val = button_data;
	}
	
	if(Alert_Timer0A) {
		print_score();
		animate_arrows(button_val);
		button_val = BTN_NONE; // after processing the button value, reset it to NONE
		Alert_Timer0A = false;
	}
	
	//clear miss/hit message on LCD
	clear_print_message();
	
	//led_blink(FAST);
}

void init_arrow_queue(void) {
	queue = create_queue();
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
		print_miss_second();
		printf("MISS: %x\n", difference);
		return MISS;
	} else if (difference <= RGN_GOOD) {
		print_hit_second();
		printf("GOOD: %x\n", difference);
		score += 10;
		return GOOD; 
	} else if (difference > RGN_GOOD) {
		print_boo_second();
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
			//printf("process_print=none\n");
			break;
		case GOOD:
			printf("process_print=good\n");
			arrow = dequeue(queue)->key;
			clear_arrow(arrow);
			print_top_arrow(arrow->arrow_type);
			break;
		case MISS:
			printf("process_print=miss\n");
			arrow = dequeue(queue)->key;
			clear_arrow(arrow);
			print_top_arrow(arrow->arrow_type);
			break;
		case BOO:
			printf("process_print=boo\n");
			break;
		default:
			printf("process_print=default\n");
			break;
	}
	
	return queue->head;
}

void print_score(void) {
	char score_arr[4]; 
	//printf("Current Score: %d", score);
	sprintf(score_arr,"%ld",(int)score);
	lcd_print_stringXY("score:",5,0, LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
	lcd_print_stringXY(score_arr,11,0, LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
}

void clear_print_message(void){
	//this is to clear the hit/miss message on LCD
	if(Alert_Timer0B) {
		static int ticks = 0;
		ticks++;
		if(ticks == PRINT_MESSAGE_DELAY){
			clear_boo();
			ticks = 0;
		}
		Alert_Timer0B = false; 
	}
}