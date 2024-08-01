#include "headers/queue.h"
#include "headers/queue.h"

Queue create_queue()
{ 
    Queue q;

    q.elements = create_linkedlist();

    return q;
}

void dealloc_queue(Queue* q) 
{ 
    dealloc_linkedlist(&q->elements); 
}

void offer(Queue* q, int val)
{ 
    append_node(&q->elements, val); 
}

int poll(Queue* q)
{
    if(is_empty(q->elements))
        exit(1);

    else
    {
        int ret = q->elements.head->val;
        delete_linkedlist_node(&q->elements, 0);
        return ret;
    }
}