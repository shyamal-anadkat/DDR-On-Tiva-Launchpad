#include "ddr_animations.h"

static queue_t *queue;

void animate_arrows() {	
	// MOVE ALL ONSCREEN ARROWS UP BY 1
	queue_node *curr_node = queue->head;
	
	while(curr_node != NULL_VALUE) {
		arrow_t *arrow = curr_node->key;
		arrow->y_pos++;
		
		print_arrow(*arrow);
		
		curr_node = curr_node->next;
	}
}

bool add_arrow(arrow_dir_t dir) {
	arrow_t *arrow = malloc(sizeof(arrow_t));
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow->arrow_type = dir;
	arrow->y_pos = ARROW_POS_START_Y;
	
	enqueue(queue, arrow);
	return true;
}

bool add_two_arrows(arrow_dir_t dir1, arrow_dir_t dir2) {
	arrow_t *arrow1 = malloc(sizeof(arrow_t));
	arrow_t *arrow2 = malloc(sizeof(arrow_t));
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow1->arrow_type = dir1;
	arrow1->y_pos = ARROW_POS_START_Y;
	arrow2->arrow_type = dir2;
	arrow2->y_pos = ARROW_POS_START_Y;
	
	enqueue(queue, arrow1);
	enqueue(queue, arrow2);
}

// ASSUMES Y POSITION OF ARROW HAS ALREADY BEEN UPDATED
void print_arrow(arrow_t arrow) {
	uint16_t x_pos;
	const uint8_t *arrow_bitmap;
	
	switch(arrow.arrow_type) {
		case ARROW_UP:
			x_pos = ARROW_POS_X_UP;
			arrow_bitmap = up_arrowBitmaps;
			break;
		case ARROW_DOWN:
			x_pos = ARROW_POS_X_DOWN;
			arrow_bitmap = down_arrowBitmaps;
			break;
		case ARROW_LEFT:
			x_pos = ARROW_POS_X_LEFT;
			arrow_bitmap = left_arrowBitmaps;
			break;
		case ARROW_RIGHT:
			x_pos = ARROW_POS_X_RIGHT;
			arrow_bitmap = right_arrowBitmaps;
			break;
	}
	
	// DRAW ARROW
	lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow.y_pos,        // Y Pos
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// Image
                  LCD_COLOR_BLUE,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
	
	// CLEAR GLITCHY BLUE TRAIL
		lcd_draw_image(
                  x_pos,              // X Pos
                  ARROW_WIDTH,   			// Image Horizontal Width
                  arrow.y_pos - ARROW_HEIGHT + 1,// Y Pos of bottom of image
                  ARROW_HEIGHT,  			// Image Vertical Height
                  arrow_bitmap, 			// DON'T CARE
                  LCD_COLOR_BLACK,     // Foreground Color
                  LCD_COLOR_BLACK     // Background Color
                );
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
	queue = create_queue();
 	lcd_clear_screen(LCD_COLOR_BLACK);
	add_arrow(ARROW_UP);
	add_arrow(ARROW_DOWN);
}

//*****************************************************************************
// Updates the entire user interface of the game in PLAY mode
// Increments all of the onscreen arrows by 1		  // Increments all of the onscreen arrows by 1
//*****************************************************************************
void update_ui_play(void) {
	animate_arrows();
}