#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node
{
    int val;
    struct node* next;
} Node; 

Node* create_node(int val, Node* next);

typedef struct
{
	int size;
	Node* head;
	Node* tail;
} LinkedList;

LinkedList create_linkedlist();
void add_node_to_front(LinkedList* ll, int val);
void append_node(LinkedList* ll, int val);
void dealloc_linkedlist(LinkedList* ll);
void print_linkedlist(LinkedList* ll) ;
void delete_linkedlist_node(LinkedList* ll, int pos);
bool is_empty(LinkedList ll);

#endif