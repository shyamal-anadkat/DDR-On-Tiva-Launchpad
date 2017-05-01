#ifndef __ARROW_QUEUE_H__
#define __ARROW_QUEUE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "arrow.h"
#include "lcd.h"

//*****************************************************************************
// ARROW QUEUE
//*****************************************************************************

#define NULL_VALUE	0

void add_arrow(arrow_dir_t dir);

typedef struct QNode {
	arrow_t *key;
	struct QNode *next;
} queue_node;

typedef struct queue {
	queue_node *head;
	queue_node *tail;
} queue_t;

void init_arrow_queue(void);
queue_node *new_node(arrow_t *arrow);
queue_t *create_queue(void);
void enqueue(queue_t *queue, arrow_t *arrow);
queue_node *dequeue(queue_t *queue);
void empty_the_queue(queue_t *queue);


#endif