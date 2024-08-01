#ifndef STACK_H
#define STACK_H

#include "linkedlist.h"

typedef struct
{
	LinkedList elements;
} Stack;

Stack create_stack();
void dealloc_stack(Stack* st);
int peek(Stack* st);
void push(Stack* st, int val);
int pop(Stack* st);

#endif