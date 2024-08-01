all:
	gcc main.c arraylist.c linkedlist.c stack.c queue.c avl.c heap.c -o run -Wall -pedantic 
clean:
	rm run
	clear
