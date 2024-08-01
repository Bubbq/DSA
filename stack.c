#include <stdlib.h>

#include "headers/stack.h"
#include "headers/linkedlist.h"

Stack create_stack()
{ 
    Stack st;

    st.elements = create_linkedlist();
    
    return st;
}

void dealloc_stack(Stack* st)
{ 
    dealloc_linkedlist(&st->elements); 
}

int peek(Stack* st)
{
    if(is_empty(st->elements)) 
        exit(1);

    else 
        return st->elements.head->val;
}

void push(Stack* st, int val) 
{ 
    add_node_to_front(&st->elements, val );
}

int pop(Stack* st)
{
    if(is_empty(st->elements)) 
        exit(1);

    else
    {
        int ret = st->elements.head->val;
        delete_linkedlist_node(&st->elements, 0);
        return ret;
    }
}