#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data_structures.h"

ArrayList createArrayList()
{
	ArrayList list;
	list.idx = 0;
	list.cap = sizeof(int) * CAP;
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

LinkedList createLinkedList()
{
	LinkedList ll;
	ll.head = NULL;
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
	while(cn != NULL)
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
    if (isEmpty(ll))
    {
        ll->head = malloc(sizeof(Node));
		ll->head->next = NULL;
        ll->head->val = val;
        ll->tail = ll->head;
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
	
	if(isEmpty(ll))
	{
		printf("TRYING TO DELETE WITH NO ELEMENTS \n");
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
		val = st->ll.head->val;
		deleteNode(&st->ll, 0);
	}

	else
	{
		printf("NO ELEMENTS TO REMOVE \n");
	}

	return val;
}

Queue createQueue()
{
	Queue q;
	q.ll = createLinkedList();
	return q;
}

void offer(Queue* q, int val)
{
	addNode(&q->ll, val);
}

int peekQueue(Queue* q)
{
	return q->ll.head->val;
}

int poll(Queue* q)
{
	int val = q->ll.head->val;
	deleteNode(&q->ll, 0);
	return val;
}

AVLTree createTree()
{
	AVLTree tree;
	tree.root = NULL;
	return tree;
}

int height(TreeNode* node)
{
	return node == NULL ? -1 : node->height;
}

// case 1 in balance function
TreeNode* rotateRight(TreeNode* a)
{		
	TreeNode* b = a->left;

	// whatevers on the right of b put it on the left of a as b is smaller than a
	a->left = b->right;

	// make b become parent of a
	b->right = a;

	// get the new, updated heights
	a->height = height(a->right) > height(a->left) ? height(a->right) + 1 : height(a->left) + 1;

	// use a bc a is now right child of b
	b->height = height(b->left) > height(a) ? height(b->left) + 1 : height(a) + 1;

	// b is the new head
	return b;
}

// case 3 in balance function
TreeNode* rotateLeft(TreeNode* a)
{
	TreeNode* b = a->right;
	
	// save the content from b left
	a->right = b->left;

	// make b the parent
	b->left = a;

	// update the height
	a->height = (height(a->left) > height(a->right)) ? height(a->left) + 1: height(a->right) + 1;

	b->height = (height(a) > height(b->right)) ? height(a) + 1 : height(b->right) + 1;

	return b;
}

// case 4 in balance function
TreeNode* doubleRotateRight(TreeNode* a)
{
	a->right = rotateRight(a->right);
	return rotateLeft(a);
}

// case 2 in balance function
TreeNode* doubleRotateLeft(TreeNode* a)
{
	a->left = rotateLeft(a->left);
	return rotateRight(a);
}

// need to check if the left and right subtrees are balanced (difference in height is <= 1)
TreeNode* balance(TreeNode* node)
{
	if(height(node->left) - height(node->right) > 1)
	{
		if(height(node->left->left) >= height(node->left->right))
		{
			/*
				case 1: long left node
					 a            b
					/            / \
				   b   -->      c   a
	              /
				 c
			*/
			node = rotateRight(node);
		}

		else
		{
			/*
				case 2: double left
				  a              a             c
				 /              /             / \  
				b     -->      c      -->    b   a
				 \            /                 
				  c          b                 
			*/
			node = doubleRotateLeft(node);
		}
	}

	if(height(node->right) - height(node->left) > 1)
	{
		if(height(node->right->right) >= height(node->right->left))
		{
			/*
			   case 3: long right node
			   a               b
				\             / \
				 b    -->    a   c
				  \
				   c
			*/
			node = rotateLeft(node);
		}
		
		else
		{
			/*
				case 4: double rotate left
				a               a              c
				 \               \            / \  
				  b  -->          c   -->    b   a
				 /                 \           
				 c                  b        
			*/
			node = doubleRotateLeft(node);
		}
	}

	// update root height
	node->height = (height(node->left) > height(node->right)) ? height(node->left) + 1: height(node->right) + 1;
	return node;
}

TreeNode* addTreeNode(TreeNode* root, int val)
{
	// base case, finding position of new node or tree is empty
	if(root == NULL)
	{
		root = malloc(sizeof(TreeNode));
		root->left = NULL;
		root->right = NULL;

		root->height = 0;
		root->val = val;
		return root;
	}

	// recursivley find the correct pos of the passed value
	if(root->val < val)
	{
		root->right = addTreeNode(root->right, val);
	}

	else if(root->val > val)
	{
		root->left = addTreeNode(root->left, val);
	}
	return balance(root);
}

TreeNode* sucessor(TreeNode* root)
{
	TreeNode* tn = root->right;

	while(tn->left != NULL)
	{
		tn = tn->left;
	}

	return tn;
}

TreeNode* deleteTreeNode(TreeNode* root, int val)
{
	// the value does not exist in the tree
	if(root == NULL)
	{
		printf("THE VALUE TO BE DELETED IS NOT IN THE TREE \n");
		exit(1);
	}

	if(root->val > val)
	{
		root->left = deleteTreeNode(root->left, val);
	}

	else if(root->val < val)
	{
		root->right = deleteTreeNode(root->right, val);
	}

	// found the node to delete
	else
	{
		// case 1: the node has only one or no children
		if(root->right == NULL && root->left == NULL)
		{
			free(root);
			return NULL;
		}

		// only right child
		else if(root->left == NULL && root->right != NULL)
		{
			TreeNode* tn = root->right;
			free(root);
			return tn;
		}

		// only left child
		else if(root->left != NULL && root->right == NULL)
		{
			TreeNode* tn = root->left;
			free(root);
			return tn;
		}

		else
		{
			// if the node has 2 children, return the smallest node in the right suAVLTreeree
			TreeNode* tn = sucessor(root);

			// replace delNodes value
			root->val = tn->val;

			// delete duplicate
			root->right = deleteTreeNode(root->right, tn->val);
		}
	}

	return balance(root);
}

int getHeight(TreeNode* root)
{
	if(root == NULL)
	{
		return 0;
	}

	int lh = getHeight(root->left);
	int rh = getHeight(root->right);

	return lh > rh ? lh + 1 : rh + 1;
}

void printAVLTree(TreeNode* root)
{
	if(root == NULL)
	{
		return;
	}

	printAVLTree(root->left);
	printf("%d  height: %d\n", root->val, root->height);
	printAVLTree(root->right);
}

void deleteAVLTree(AVLTree* AVLTree)
{
	while(AVLTree->root != NULL)
	{
		AVLTree->root = deleteTreeNode(AVLTree->root, AVLTree->root->val);
	}
}

Graph createGraph()
{
	Graph g;
	g.edge.all_edges = malloc(CAP * sizeof(Edge));
	g.edge.cap = CAP * sizeof(Edge);
	g.edge.size = 0;

	memset(g.nodes, 0, sizeof(g.nodes));

	// instantiate adj nodes
	for(int i = 0; i < CAP; i++)
	{
		g.nodes[i].adjn = createArrayList();
	}

	return g;
}

void deleteGraph(Graph* g)
{
	for(int i = 0; i < CAP; i++)
	{
		deleteArrayList(&g->nodes[i].adjn);
	}

	free(g->edge.all_edges);
}

// adding edge from node a to b
void addEdge(Graph* g, int a, int b, int w)
{
	if(a > CAP - 1 || b > CAP)
	{
		printf("invalid src or dst position \n");
		return;
	}

	// checking if node b is alr an adj node to a
	for(int i = 0; i < g->nodes[a].adjn.idx; i++)
	{
		if(g->nodes[a].adjn.arr[i] == b)
		{
			printf("node b is already in a \n");
			return;
		}
	}

	// update src vertex's adj nodes
	add(&g->nodes[a].adjn, b);
	g->nodes[a].val = a;
	g->nodes[b].val = b;

	// update in and out degrees
	g->nodes[a].out_degree++;
	g->nodes[b].in_degree++;

	// update graphs edges
	if(g->edge.size * sizeof(Edge) == g->edge.cap)
	{
		g->edge.cap *= 2;
		g->edge.all_edges = realloc(g->edge.all_edges, g->edge.cap);
	}

	g->edge.all_edges[g->edge.size++] = (Edge){w, a, b};
}

// remove connection from node a to b
void deleteEdge(Graph* g, int a, int b)
{
	if(a > CAP - 1 || b > CAP - 1)
	{
		printf("INVALID NODE POSITION \n");
		return;
	}

	int pos = -1;

	// remove the adjacency
	for(int i = 0; i < g->nodes[a].adjn.idx; i++)
	{
		if(g->nodes[a].adjn.arr[i] == b)
		{
			pos = i;
			delete(&g->nodes[a].adjn, i);
			// update in and out degree
			g->nodes[a].out_degree--;
			g->nodes[b].in_degree--;
			g->nodes[b].val = 0;
		}
	}

	// flag to shift elements to the left
	bool shift = false;

	// remove edge
	for(int i = 0; i < g->edge.size; i++)
	{
		if(g->edge.all_edges[i].src == a && g->edge.all_edges[i].dst == b)
		{
			shift = true;
			g->edge.size--;
		}

		if(shift)
		{
			g->edge.all_edges[i] = g->edge.all_edges[i + 1];
		}
	}

	if(pos < 0)
	{
		printf("node %d does not connect to %d \n", a, b);
		return;
	}
}

bool checkEdge(Graph*g,  int a, int b)
{
	if(a > CAP - 1 || b > CAP - 1)
	{
		printf("invalid src or dst position \n");
		return false;
	}

	for(int i = 0; i < g->nodes[a].adjn.idx; i++)
	{
		if(g->nodes[a].adjn.arr[i] == b)
		{
			return true;
		}
	}

	return false;
}

void printGraph(Graph* g)
{
    printf("NODE\tIN\tOUT\tDIST\tEDGE(S)\n");
    for(int i = 0; i < CAP; i++)
    {
		if(g->nodes[i].val <= 0)
		{
			continue;
		}

        printf("%d\t%d\t%d\t%d\t", i, g->nodes[i].in_degree, g->nodes[i].out_degree, g->nodes[i].dist);
        for(int j = 0; j < g->nodes[i].adjn.idx; j++)
        {
            printf("%d ", g->nodes[i].adjn.arr[j]);
        }
		
        printf("\n");
    }
}

// depth first search at some starting node
void DFS(Graph* g, int s)
{
    bool visited[CAP] = {false};

    Stack dfs = createStack();
    push(&dfs, s);
    printf("DFS Order: ");

    while (!isEmpty(&dfs.ll))
    {
		int cn = pop(&dfs);
		printf("%d ", cn);
		for(int i = g->nodes[cn].adjn.idx - 1; i >= 0; i--)
		{
			int adjn = g->nodes[cn].adjn.arr[i];
			if(!visited[adjn])
			{
				visited[adjn] = true;
				push(&dfs, adjn);
			}
		}
    }
}

// breadth first search at some starting node
void BFS(Graph* g, int s)
{
	// flags for wether we have visited a node or not
	bool visited [CAP] = {false};
	Queue bfs = createQueue();
	offer(&bfs, s);
	printf("BFS Order: ");
	
	while(!isEmpty(&bfs.ll))
	{
		int cn = poll(&bfs);
		printf("%d ", cn);	
		
		for(int i = 0; i < g->nodes[cn].adjn.idx; i++)
		{
			int adjn = g->nodes[cn].adjn.arr[i];
			if(!visited[adjn])
			{
				visited[adjn] = true;
				offer(&bfs, adjn);
			}
		}
	}
}

int shortestPath(Graph* g, int a, int b)
{
	// flag determining wether we have met these nodes or not, prevents cycling
	bool visited[CAP] = {false};

	// to hold nodes and their path lengths in BFS order
	Queue n = createQueue();
	Queue pl = createQueue();

	// add the starting node a, trying to get to b
	offer(&n, a);
	offer(&pl, 0);

	while(!isEmpty(&n.ll))
	{
		// get the current nodes and its distance from the src node a
		int cn = poll(&n);
		int d = poll(&pl);

		// if we have reached node b, return the shortest length
		if(cn == b)
		{
			printf("the shortest path length from node %d to node %d is %d \n", a, b, d);
			deleteLinkedList(&n.ll);
			deleteLinkedList(&pl.ll);

			return d;
		}

		// if not, add all adj nodes
		for(int i = 0; i < g->nodes[cn].adjn.idx; i++)
		{
			// if we have an edge and have not prevoisly met this node before, add it to the queue
			int adjn = g->nodes[cn].adjn.arr[i];
			if(!visited[adjn])
			{
				visited[adjn] = true;
				offer(&n, adjn);
				offer(&pl, d + 1);
			}
		}
	}

	// at this point, there is no possible path from a to b
	deleteLinkedList(&n.ll);
	deleteLinkedList(&pl.ll);
	return -1;
}

void topologicalSort(Graph g)
{
	// store every node with in-degree of 0 in a queue
	Queue q = createQueue();
	
	for(int i = 0; i < CAP; i++)
	{
		if(g.nodes[i].in_degree == 0 && g.nodes[i].val > 0)
		{
			offer(&q, i);
		}
	}
	
	printf("Topologically Sorted: ");
	while(!isEmpty(&q.ll))
	{
		// get the next node of in-degree 0 and print it
		int cn = poll(&q);		
		printf("%d ", cn);
		
		// "remove" node by removing all its links
		for(int i = 0; i < g.nodes[cn].adjn.idx; i++)
		{
			int adjn = g.nodes[cn].adjn.arr[i];
			g.nodes[adjn].in_degree--;
			
			// add any 0 in-degree nodes, if any
			if(g.nodes[adjn].in_degree == 0)
			{
				offer(&q, adjn);
			}	
		}
	}
}

void printEdges(Graph* g)
{
	printf("SRC\tDST\tWEIGHT \n");
	for(int i = 0; i < g->edge.size; i++)
	{
		Edge e = g->edge.all_edges[i];
		printf("%d\t%d\t%d\n", e.src, e.dst, e.weight);
	}
}

void shuffleEdges(Edges* edges)
{
	srand(time(NULL)); // Seed the random number generator
    for (int i = edges->size - 1; i >= 0; i--) {
        int j = rand() % (i + 1); // Generate a random index between 0 and i
        // Swap arr[i] and arr[j]
        Edge tmp = edges->all_edges[i];
        edges->all_edges[i] = edges->all_edges[j];
        edges->all_edges[j] = tmp;
    }
}

void bellmanFord(Graph* g, int start)
{
	// set the distance of all nodes to infinity
	for(int i = 0; i < CAP; i++)
	{
		g->nodes[i].dist = 999;
	}

	// amount of updates relaxing E edges, when this is 0, algorithim is done
	int changes;

	// for the starting node
	g->nodes[start].dist = 0;
	do
	{
		changes = 0;
		// generate random permuation of edges
		shuffleEdges(&g->edge);

		// relax every edge if possible
		for(int i = 0; i < g->edge.size; i++)
		{
			int src = g->edge.all_edges[i].src;
			int dst = g->edge.all_edges[i].dst;
			int w = g->edge.all_edges[i].weight;

			if(g->nodes[src].dist + w < g->nodes[dst].dist)
			{
				changes++;
				g->nodes[dst].dist = g->nodes[src].dist + w;
			}
		}

	} while(changes != 0);
}

Heap createHeap()
{
	return (Heap){createArrayList()};
}

void deleteHeap(Heap* heap)
{
	deleteArrayList(&heap->elements);
}

int parent(int cidx)
{
	return (cidx - 1) / 2 >= 0 ? (cidx - 1) / 2 : -1; 
}

int leftChild(Heap* heap, int cidx)
{
	return (2 * cidx) + 1 <= heap->elements.idx - 1 ? (2 * cidx) + 1 : -1;
}

int rightChild(Heap* heap, int cidx)
{
	return (2 * cidx) + 2 <= heap->elements.idx - 1 ? (2 * cidx) + 2 : -1;
}

void heapifyUp(Heap* heap, int start)
{
	// while the new element has a parent, if its smaller than it, then swap
	while(parent(start) != -1 && heap->elements.arr[start] < heap->elements.arr[parent(start)])
	{
		int tmp = heap->elements.arr[start];
		heap->elements.arr[start] = heap->elements.arr[parent(start)];
		heap->elements.arr[parent(start)] = tmp;

		// update current index
		start = parent(start);
	}
}

void heapifyDown(Heap* heap)
{
	int cidx = 0;

	while(leftChild(heap, cidx) != -1)
	{
		int lc = leftChild(heap, cidx);
		int rc = rightChild(heap, cidx);
		int small = leftChild(heap, cidx);

		// check if right child exists and if its actually smaller than left
		if(rc != -1)
		{
			small = heap->elements.arr[lc] < heap->elements.arr[rc] ? lc : rc;
		}

		// check if we need to swap
		if(heap->elements.arr[cidx] <= heap->elements.arr[small])
		{
			break;
		}

		// swap the current element with is smaller child
		int tmp = heap->elements.arr[cidx];
		heap->elements.arr[cidx] = heap->elements.arr[small];
		heap->elements.arr[small] = tmp;

		// update index
		cidx = small;
	}

}

void addHeapElement(Heap* heap, int val)
{
	add(&heap->elements, val);
	heapifyUp(heap, heap->elements.idx - 1);
}

void deleteMin(Heap* heap)
{
	if(heap->elements.idx == 0)
	{
		printf("REMOVING WITH NO ELEMENTS \n");
		return;
	}

	// set root to last element and delete duplicate
	heap->elements.arr[0] = heap->elements.arr[heap->elements.idx - 1];
	delete(&heap->elements, heap->elements.idx - 1);

	// adj temp root to correct position
	heapifyDown(heap);
}

void deleteHeapElement(Heap* heap, int pos)
{
	if(pos < 0 || pos > heap->elements.idx - 1)
	{
		printf("INVALID POS \n");
		return;
	}

	if(heap->elements.idx == 1)
	{
		deleteMin(heap);
	}

	// make element smallest in heap
	heap->elements.arr[pos] = heap->elements.arr[0] - 1;

	// move heap to root position
	heapifyUp(heap, pos);

	// remove psuedo root
	deleteMin(heap);
}

int main()
{
	// --------------- INIT ----------------------//	
	ArrayList list = createArrayList();
	LinkedList ll = createLinkedList();
	Stack st = createStack();
	Queue q = createQueue();
	AVLTree AVLTree = createTree();
	Graph g = createGraph();
	Heap heap = createHeap();
	// --------------- INIT ----------------------//	

	// --------------- ADDDING ----------------------//	
	addEdge(&g,1,2, 2);
	addEdge(&g,1,4, 1);

	addEdge(&g,2,4, 3);
	addEdge(&g,2,5, 10);

	addEdge(&g,3,6, 5);
	addEdge(&g,3,1, 4);
	
	addEdge(&g,4,6, 8);
	addEdge(&g,4,3, 2);
	addEdge(&g,4,7, 4);
	addEdge(&g,4,5, 2);

	addEdge(&g,5,7, 6);

	addEdge(&g,7,6, 1);

	for(int i = 32; i >= 0; i--)
	{
		addHeapElement(&heap, i);
		add(&list, i);
		addNode(&ll, i);
		push(&st, i);
		offer(&q, i);
		AVLTree.root = addTreeNode(AVLTree.root, i);
	}
	// --------------- ADDDING ----------------------//	

	// --------------- PRINTING ----------------------//
	// printArrayList(&heap.elements);	
	// printLinkedList(&ll);
	// printAVLTree(AVLTree.root);
	// printGraph(&g);
	// --------------- PRINTING ----------------------//	

	// --------------- DEINIT ----------------------//	
	deleteArrayList(&list);
	deleteLinkedList(&ll);
	deleteLinkedList(&st.ll);
	deleteLinkedList(&q.ll);
	deleteAVLTree(&AVLTree); 
	deleteGraph(&g);
	deleteHeap(&heap);
	return 0;
	// --------------- DEINIT ----------------------//	
}