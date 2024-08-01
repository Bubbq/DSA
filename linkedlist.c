#include "headers/linkedlist.h"

Node* create_node(int val, Node* next)
{
    Node* nn = malloc(sizeof(Node));
    
	nn->val = val;
	nn->next = next;

    return nn;
}

LinkedList create_linkedlist()
{ 
	LinkedList ll;

	ll.size = 0;
	ll.tail = ll.head = create_node(-1, NULL);

	return ll;
}

void add_node_to_front(LinkedList* ll, int val)
{
	if(is_empty(*ll))
		ll->head->val = val;

	else
	{
		Node* new_head = create_node(val, ll->head);
		ll->head = new_head;	
	}

	ll->size++;
}

void append_node(LinkedList* ll, int val)
{
	if(is_empty(*ll))
		ll->head->val = val;
	
    else
    {
        ll->tail->next = create_node(val, NULL);
        ll->tail = ll->tail->next;
    }

    ll->size++;
}

void delete_linkedlist_node(LinkedList* ll, int pos)
{
	if((pos < 0) || (pos > ll->size))
	{
		printf("ERROR, ACCESSING ELEMENT OUT OF BOUNDS!\n");
		return;
	}
    
	// empty list error check
	else if(ll->size == 0)
	{
		printf("ERROR, REMOVING WITH NO ELEMENTS!\n");
		return;
	}
    
	else
    { 
        Node* prev = NULL;
        Node* cn = ll->head;

        for(int i = 0; i < pos; i++, prev = cn, cn = cn->next)
			;

		// deleting the root
        if(prev == NULL) 
        {
            prev = ll->head;
            ll->head = ll->head->next;
            free(prev);
        }
        
        else 
        {
            prev->next = cn->next;
            free(cn);
        }

        ll->size--;
    }
}

void print_linkedlist(LinkedList* ll) 
{ 
	for(Node* node = ll->head; node != NULL; node = node->next)
		printf("%d ", node->val);
}

void dealloc_linkedlist(LinkedList* ll)
{ 
	for(Node* prev = NULL; ll->head != NULL; prev = ll->head, ll->head = ll->head->next, free(prev))
		; 
}

bool is_empty(LinkedList ll)
{
    return (ll.size == 0);
}