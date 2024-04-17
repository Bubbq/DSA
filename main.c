#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>

const int ARRAY_SIZE = 10;

typedef struct
{
	int* arr;
	int idx;
	size_t cap;
} ArrayList;

ArrayList createArrayList()
{
	ArrayList list;
	list.idx = 0;
	list.cap = sizeof(int) * ARRAY_SIZE;
	list.arr = malloc(list.cap);
	return list;
}

void resize(ArrayList* list)
{
	list->cap *= 2;
	list->arr = realloc(list->arr, list->cap);

	if(list->arr == NULL)
	{
		printf("RESIZING FAILED \n");
		exit(1);
	}
}

void add(ArrayList* list, int val)
{
	if(list->idx * sizeof(int) == list->cap)
	{
		resize(list);
	}

	list->arr[list->idx++] = val;
}

void deleteArrayList(ArrayList* list)
{
	free(list->arr);
}

void delete(ArrayList* list, int pos)
{
	if(pos < 0 || pos >= list->idx)
	{
		printf("INVALID INDEX \n");
	}
	
	for(int i = pos; i < list->idx; i++)
	{
		list->arr[i] = list->arr[i + 1];
	}
	
	list->idx--;
}

void printArrayList(ArrayList* list)
{
	for(int i = 0; i < list->idx; i++)
	{
		printf("%d ", list->arr[i]);
	}
}

// how to  solve recusive definition in c
typedef struct node
{
    int val;
    struct node* next;
} Node; 

typedef struct
{
	Node* head;
	Node* tail;
	int size;
} LinkedList;

LinkedList createLinkedList()
{
	LinkedList ll;
	ll.head = malloc(sizeof(Node));
	ll.tail = ll.head;
	ll.size = 0;
	return ll;
}

bool isEmpty(LinkedList* ll)
{
	return ll->size == 0;
}

void printLinkedList(LinkedList* ll)
{
	Node* cn = ll->head;
	while(cn->next != NULL)
	{
		printf("%d ", cn->val);
		cn = cn->next;
	}
}

void addFront(LinkedList* ll, int val)
{
	Node* nh = malloc(sizeof(Node));
	nh->val = val;
	nh->next = ll->head;
	ll->head = nh;
	ll->size++;
}

void addNode(LinkedList* ll, int val)
{
	if(ll->size == 0)
	{
		ll->head->val = val;
	}

	else
	{
		ll->tail->next = malloc(sizeof(Node));
		ll->tail->next->val = val;
		ll->tail = ll->tail->next;
	}

	ll->size++;
}

void deleteNode(LinkedList* ll, int pos)
{
	if(pos < 0 || pos > ll->size)
	{
		printf("INVAILD POS TO DELETE \n");
		return;
	}
	
	Node* cn = ll->head;
	Node* prev = NULL;

	int itr = 0;
	while(itr != pos)
	{
		prev = cn;
		cn = cn->next;
		itr++;
	}

	// deleting root
	if(prev == NULL)
	{
		prev = ll->head;
		ll->head = ll->head->next;
	}

	else
	{
		prev->next = cn->next;
	}

	free(cn);

	ll->size--;
}

void deleteLinkedList(LinkedList* ll)
{
	Node* prev = NULL;
	
	while(ll->head != NULL)
	{
		prev = ll->head;
		ll->head = ll->head->next;
		free(prev);
	}
}

typedef struct
{
	LinkedList ll;
} Stack;

Stack createStack()
{
	Stack st;
	st.ll = createLinkedList();
	return st;
}

void push(Stack* st, int val)
{
	addFront(&st->ll, val);
}

int peek(Stack* st)
{
	return st->ll.head->val;
}

int pop(Stack* st)
{
	int val = -1;

	if(!isEmpty(&st->ll))
	{
		deleteNode(&st->ll, 0);
	}

	else
	{
		printf("NO ELEMENTS TO REMOVE \n");
	}

	return val;
}

int main()
{
	ArrayList list = createArrayList();
	LinkedList ll = createLinkedList();
	Stack st = createStack();

	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		add(&list, i);
		addNode(&ll, i);
		push(&st, i);
	}

	deleteArrayList(&list);
	deleteLinkedList(&ll);
	deleteLinkedList(&st.ll);
	
	return 0;
}