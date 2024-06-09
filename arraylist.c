#include <stdio.h>
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

int main()
{
    ArrayList al = createArrayList();
    deleteArrayList(&al);
    return 0;
}
