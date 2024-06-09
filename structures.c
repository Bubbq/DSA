#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 10

typedef struct
{
	int* list;
	int size;
	size_t cap;
} ArrayList;

ArrayList createArrayList()
{
    return (ArrayList){malloc(CAP * sizeof(int)), 0, sizeof(int) * CAP};
}

void deleteArrayList(ArrayList* al)
{
    free(al->list);
}

void deleteElement(ArrayList* al, int p)
{
    if((p < 0) || (p > al->size)) 
    {
        printf("invalid delete position\n");
        return;
    }

    else 
    {
        for(int i = p; i < al->size - 1; i++) al->list[i] = al->list[i + 1];
        al->size--;
    }
}

void resize(ArrayList* al)
{
    al->cap *= 2;
    al->list = realloc(al->list, al->cap);
}

void addElement(ArrayList* al, int n)
{
    if(al->size * sizeof(int) == al->cap) resize(al);
    al->list[al->size++] = n;
}

void printArrayList(ArrayList* al)
{
    for(int i = 0; i < al->size; i++) printf("%d ", al->list[i]);
}
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

LinkedList createLinkedList()
{
    return (LinkedList){0, NULL, NULL};
}

void deleteLinkedList(LinkedList* ll)
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

typedef struct
{
	LinkedList elements;
} Stack;

Stack createStack()
{
    return (Stack){createLinkedList()};
}

void deleteStack(Stack* st)
{
    deleteLinkedList(&st->elements);
}

int peek(Stack* st)
{
    if(isEmpty(st->elements))
    {
        printf("no elements to return\n");
        exit(1);
    }

    return st->elements.head->val;
}

void push(Stack* st, int val)
{
    addFront(&st->elements, val);
}

int pop(Stack* st)
{
    if(isEmpty(st->elements))
    {
        printf("no elements to delete\n");
        exit(1);
    }

    int ret = st->elements.head->val;
    deleteNode(&st->elements, 0);
    return ret;
}

typedef struct
{
	LinkedList elements;
} Queue;

Queue createQueue()
{
    return (Queue){createLinkedList()};
}

void deleteQueue(Queue* q)
{
    deleteLinkedList(&q->elements);
}

void offer(Queue* q, int val)
{
    addBack(&q->elements, val);
}

int poll(Queue* q)
{
    if(isEmpty(q->elements))
    {
        printf("no elements to delete\n");
        exit(1);
    }

    else
    {
        int ret = q->elements.head->val;
        deleteNode(&q->elements, 0);
        return ret;
    }
}

int main()
{
    ArrayList al = createArrayList();
    LinkedList ll = createLinkedList();
    Stack st = createStack();
    Queue q = createQueue();

    for(int i = 0; i < CAP; i++)
    {
        addElement(&al, i);
        addBack(&ll, i);
        push(&st, i);
        offer(&q, i);
    }

    deleteQueue(&q);
    deleteArrayList(&al);
    deleteLinkedList(&ll);
    deleteStack(&st);
    return 0;
}