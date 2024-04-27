#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CAP 10

typedef struct
{
	int* arr;
	int idx;
	size_t cap;
} ArrayList;

ArrayList newArrayList();
void resize(ArrayList*);
void addElement(ArrayList*,int);
void printArrayList(ArrayList*);
void deleteElement(ArrayList*,int);
void deleteArrayList(ArrayList*);

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

LinkedList createLinkedList();
bool isEmpty(LinkedList* ll);
void printLinkedList(LinkedList* ll);
void addFront(LinkedList* ll, int val);
void addNode(LinkedList* ll, int val);
void deleteNode(LinkedList* ll, int pos);
void deleteLinkedList(LinkedList* ll);

typedef struct
{
	LinkedList ll;
} Stack;

Stack createStack();
void push(Stack* st, int val);
int peek(Stack* st);
int pop(Stack* st);

typedef struct
{
	LinkedList ll;
} Queue;

Queue createQueue();
void offer(Queue* q, int val);
int peekQueue(Queue* q);
int poll(Queue* q);

typedef struct tree_node
{
	int val;
	struct tree_node* left;
	struct tree_node* right;
	int height;
} TreeNode;

typedef struct
{
	TreeNode* root;
} AVLTree;

AVLTree createTree();
void deleteAVLTree(AVLTree* AVLTree);
int height(TreeNode* node);
TreeNode* rotateRight(TreeNode* a);
TreeNode* rotateLeft(TreeNode* a);
TreeNode* doubleRotateRight(TreeNode* a);
TreeNode* doubleRotateLeft(TreeNode* a);
TreeNode* balance(TreeNode* node);
TreeNode* addTreeNode(TreeNode* root, int val);
TreeNode* sucessor(TreeNode* root);
TreeNode* deleteTreeNode(TreeNode* root, int val);
void printAVLTree(TreeNode* root);

typedef struct
{
	int weight;
	int src;
	int dst;
} Edge;

typedef struct
{
	Edge* all_edges;
	int size;
	int cap;
} Edges;

typedef struct
{
	int dist;
	int val;
	int in_degree;
	int out_degree;
	// list of adjacent nodes
	ArrayList adjn;
} Vertex;

typedef struct
{
	Vertex nodes[CAP];
	Edges edge;
} Graph;

Graph createGraph();
void deleteGraph(Graph* g);
void addEdge(Graph* g, int a, int b, int w);
void deleteEdge(Graph* g, int a, int b);
bool checkEdge(Graph*g,  int a, int b);
void printGraph(Graph* g);
void DFS(Graph* g, int s);
void BFS(Graph* g, int s);
int shortestPath(Graph* g, int a, int b);
void topologicalSort(Graph g);
void printEdges(Graph* g);
void shuffleEdges(Edges* edges);
void bellmanFord(Graph* g, int start);

typedef struct
{
	ArrayList elements;
} Heap;

Heap createHeap();
void deleteHeap(Heap* heap);
int parent(int cidx);
int leftChild(Heap* heap, int cidx);
int rightChild(Heap* heap, int cidx);
void heapifyUp(Heap* heap, int start);
void heapifyDown(Heap* heap);
void addHeapElement(Heap* heap, int val);
void deleteMin(Heap* heap);
void deleteHeapElement(Heap* heap, int pos);