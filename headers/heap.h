#ifndef HEAP_H
#define HEAP_H

#include "arraylist.h"

typedef struct
{
	ArrayList list;
} Heap;

Heap create_heap();
void dealloc_heap(Heap* heap);
int parent_position(int pos) ;
int left_child_position(Heap* heap, int cidx);
int right_child_position(Heap* heap, int cidx);
void swap(int* i, int* j);
void heapify_up(Heap* heap, int pos);
void heapify_down(Heap* heap);
void add_heap_element(Heap* heap, int val);
void delete_min_element(Heap* heap);
void deleteHeapElement(Heap* heap, int pos);
void print_heap(Heap* heap) ;

#endif