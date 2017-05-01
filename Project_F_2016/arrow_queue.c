#include "arrow_queue.h"

queue_t *queue;


//*****************************************************************************
// ARROW QUEUE
//*****************************************************************************
void init_arrow_queue(void) {
	queue = create_queue();
}

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


// TODO: This doesn't have to be a boolean anymore
void add_arrow(arrow_dir_t dir) {
	arrow_t *arrow = malloc(sizeof(arrow_t));
	
	// Instantiate arrow structs to add to arrows_on_screen array
	arrow->arrow_type = dir;
	arrow->y_pos = ARROW_POS_START_Y;
	arrow->color = LCD_COLOR_BLUE;
	
	enqueue(queue, arrow);
}

// Empties the arrow queue
// Ideal usages are when the player loses the game or goes to main menu
void empty_the_queue(queue_t *queue) {
	queue_node *temp = queue->head;
	
	if(queue->head == NULL_VALUE && queue->tail == NULL_VALUE) return;
	
	while(temp != NULL_VALUE) {
		temp = dequeue(queue);
	}
}

