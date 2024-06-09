#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 10

typedef struct node
{
    int val;
    struct node* next;
} Node; 

Node* createNode(int val, Node* next)
{
    Node* nn = malloc(sizeof(Node));
    *nn = (Node){val, next};
    return nn;
}

typedef struct
{
	int size;
	Node* head;
	Node* tail;
} LinkedList;

LinkedList create()
{
    return (LinkedList){0, NULL, NULL};
}

void delete(LinkedList* ll)
{
    while(ll->head != NULL)
    {
        Node* prev = ll->head;
        ll->head = ll->head->next;
        free(prev);
    }
}

bool isEmpty(LinkedList ll)
{
    return (ll.size == 0);
}

void print(LinkedList ll)
{
    for(; ll.head != NULL; ll.head = ll.head->next) printf("%d ", ll.head->val);
}

void addFront(LinkedList* ll, int val)
{
    Node* nh = createNode(val, ll->head);
    ll->head = nh;
    ll->size++;
}

void addBack(LinkedList* ll, int val)
{
    if(isEmpty(*ll))
    {
        ll->head = createNode(val, NULL);
        ll->tail = ll->head;
    }

    else
    {
        ll->tail->next = createNode(val, NULL);
        ll->tail = ll->tail->next;
    }

    ll->size++;
}

void deleteNode(LinkedList* ll, int pos)
{
    if((pos < 0) || (pos > ll->size))
    {
        printf("invalid delete position\n");
        return;
    }

    else if(isEmpty(*ll))
    {
        printf("invalid number of nodes to delete\n");
        return;
    }

    else
    { 
        Node* prev = NULL;
        Node* cn = ll->head;

        for(int i = 0; i < pos; i++, prev = cn, cn = cn->next);

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

int main()
{
    LinkedList ll = create();
    delete(&ll);
    return 0;
}