#include "headers/heap.h"

Heap create_heap()
{ 
    Heap h;

    h.list = create_array_list();

    return h;
}

void dealloc_heap(Heap* heap)
{ 
    dealloc_arraylist(&heap->list);
}

int parent_position(int pos) 
{ 
    return (pos - 1) / 2 >= 0 ? (pos - 1) / 2 : -1;
}

int left_child_position(Heap* heap, int cidx)
{ 
    return (2 * cidx) + 1 <= heap->list.size - 1 ? (2 * cidx) + 1 : -1;
}

int right_child_position(Heap* heap, int cidx)
{ 
    return (2 * cidx) + 2 <= heap->list.size - 1 ? (2 * cidx) + 2 : -1;
}

void swap(int* i, int* j)
{
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

void heapify_up(Heap* heap, int pos)
{
	// while the current element has a parent and is smaller, continue to swap the two
	while(parent_position(pos) != -1 && heap->list.elements[pos] < heap->list.elements[parent_position(pos)])
	{
		swap(&heap->list.elements[pos], &heap->list.elements[parent_position(pos)]);
		
		// update current index
		pos = parent_position(pos);
	}
}

void heapify_down(Heap* heap)
{
	int cidx = 0;

	while(left_child_position(heap, cidx) != -1)
	{
		int lc = left_child_position(heap, cidx);
		int rc = right_child_position(heap, cidx);
		
		// position of smaller child value 
		int sp;

		// check if right child exists and if its actually smaller than left
		if(rc == -1)
            sp = lc;
		else 
            sp = (heap->list.elements[lc] < heap->list.elements[rc]) ? lc : rc;

		// check if we need to swap
		if(heap->list.elements[cidx] <= heap->list.elements[sp])
             break;

		swap(&heap->list.elements[cidx], &heap->list.elements[sp]);

		// update index
		cidx = sp;
	}
}

void add_heap_element(Heap* heap, int val)
{
	add_arraylist_element(&heap->list, val);
	heapify_up(heap, (heap->list.size - 1));
}

void delete_min_element(Heap* heap)
{
	if(heap->list.size == 0) return;

	// set root to last element and delete duplicate
	heap->list.elements[0] = heap->list.elements[(heap->list.size - 1)];
	remove_arraylist_element(&heap->list, (heap->list.size - 1));

	// adj temp root to correct position
	heapify_down(heap);
}

void deleteHeapElement(Heap* heap, int pos)
{
	// out of bounds error check
	if(pos < 0 || (pos > heap->list.size - 1)) return;

	// make element smallest in heap
	heap->list.elements[pos] = heap->list.elements[0] - 1;

	// move heap to root position
	heapify_up(heap, pos);

	// remove psuedo root
	delete_min_element(heap);
}

void print_heap(Heap* heap) 
{ 
    print_arraylist(&heap->list);
}
