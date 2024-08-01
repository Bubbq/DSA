#include <stdio.h>

#include "headers/linkedlist.h"
#include "headers/arraylist.h"
#include "headers/queue.h"
#include "headers/stack.h"
#include "headers/heap.h"
#include "headers/avl.h"

int main()
{
    // -----------INIT-----------------
	ArrayList al = create_array_list();
    LinkedList ll = create_linkedlist();
    Stack st = create_stack();
    Queue q = create_queue();
    AVLTree avl = create_avl_tree();
	Heap heap = create_heap();

	// ----------ADDING-------------
    for(int i = 0; i < 10; i++)
    {
        add_arraylist_element(&al, i);
        append_node(&ll, i);
        push(&st, i);
        offer(&q, i);
        avl.root = add_tree_node(avl.root, i);
		add_heap_element(&heap, i);
	}

	// ----------PRINTING-------------
	// print_arraylist(&al);
    // print_linkedlist(&ll);
    // inorder_avl_tree_traversal(avl.root);
	// print_heap(&heap);
	

	// ----------DELLAOCATION---------
    dealloc_arraylist(&al);
    dealloc_queue(&q);
    dealloc_linkedlist(&ll);
    dealloc_stack(&st);
    dealloc_avl_tree(&avl);
	dealloc_heap(&heap);

    return 0;
}