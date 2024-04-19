#include <stdio.h>
#include <stdbool.h>
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

typedef struct
{
	LinkedList ll;
} Queue;

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
} BST;

BST createTree()
{
	BST tree;
	tree.root = NULL;
	return tree;
}

TreeNode* addTreeNode(TreeNode* root, int val)
{
	// base case, the tree is empty
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

	else
	{
		printf("CANNOT ADD TWO ELEMENTS WITH THE SAME VALUE \n");
		exit(1);
	}

	return root;
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
			// if the node has 2 children, return the smallest node in the right suBSTree
			TreeNode* tn = sucessor(root);

			// replace delNodes value
			root->val = tn->val;

			// delete duplicate
			root->right = deleteTreeNode(root->right, tn->val);
		}
	}

	return root;
}

void printBST(TreeNode* root)
{
	if(root == NULL)
	{
		return;
	}

	printBST(root->left);
	printf("%d ", root->val);
	printBST(root->right);
}

void deleteBST(BST* BST)
{
	while(BST->root != NULL)
	{
		BST->root = deleteTreeNode(BST->root, BST->root->val);
	}
}

int main()
{
	// ArrayList list = createArrayList();
	// LinkedList ll = createLinkedList();
	// Stack st = createStack();
	// Queue q = createQueue();
	BST BST = createTree();

	int arr[] = {4, 2, 6, 1, 3, 5, 7};

	for(int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		// add(&list, i);
		// addNode(&ll, i);
		// push(&st, i);
		// offer(&q, i);
		BST.root = addTreeNode(BST.root, arr[i]);
	}

	printBST(BST.root);
	// deleteArrayList(&list);
	// deleteLinkedList(&ll);
	// deleteLinkedList(&st.ll);
	// deleteLinkedList(&q.ll);	
	deleteBST(&BST); 
	return 0;
}
