#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"

typedef struct
{
	LinkedList elements;
} Queue;

Queue create_queue();
void dealloc_queue(Queue* q);
void offer(Queue* q, int val);
int poll(Queue* q);

#endif