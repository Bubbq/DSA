#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int size;
	int* elements;
	size_t mem_capacity;
} ArrayList;

ArrayList create_array_list();
void resize(ArrayList* al);
void add_arraylist_element(ArrayList* al, int n);
void remove_arraylist_element(ArrayList* al, int position);
void print_arraylist(ArrayList* al);
void dealloc_arraylist(ArrayList* alloc_al_mem);

#endif