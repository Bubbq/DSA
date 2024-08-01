
#include "headers/arraylist.h"

ArrayList create_array_list()
{ 
	ArrayList al;
	
	al.size = 0;
	al.mem_capacity = (sizeof(int));
	al.elements = malloc(al.mem_capacity);

	return al;
}

void resize(ArrayList* al)
{
    al->mem_capacity *= 2;
    al->elements = realloc(al->elements, al->mem_capacity);
}

void add_arraylist_element(ArrayList* al, int val)
{
    if(al->size * sizeof(int) == al->mem_capacity) 
		resize(al);
    
	al->elements[al->size++] = val;
}

void remove_arraylist_element(ArrayList* al, int position)
{
    if((position > al->size) || (position < 0))
	{
		printf("ERROR, ACCESSING ELEMENT OUT OF BOUNDS! \n");
		return;
	}

	// shift every element to the left once
	for(int i = position; i < al->size; i++)
		al->elements[i] = al->elements[i + 1];
	
	al->size--;
}

void print_arraylist(ArrayList* al) 
{ 
	for(int i = 0; i < al->size; i++)
		printf("%d ", al->elements[i]);
}

void dealloc_arraylist(ArrayList* alloc_al_mem)
{ 
	free(alloc_al_mem->elements); 
}