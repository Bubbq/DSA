#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 10
#define AL = sizeof(int * CAP)

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
    if((p < 0) || (p > al->size)) return;

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
    for(Node* prev = NULL; ll->head != NULL; prev = ll->head, ll->head = ll->head->next, free(prev));
}

bool isEmpty(LinkedList ll)
{
    return (ll.size == 0);
}

void printLinkedList(LinkedList ll)
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
    if((pos < 0) || (pos > ll->size)) return;
    else if(isEmpty(*ll)) return;
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
    if(isEmpty(st->elements)) return -1;

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
    if(isEmpty(q->elements)) return -1;

    else
    {
        int ret = q->elements.head->val;
        deleteNode(&q->elements, 0);
        return ret;
    }
}

typedef struct tree_node
{
	int val;
	int height;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;

TreeNode* createTreeNode(int val)
{
    TreeNode* tn = malloc(sizeof(TreeNode));
    *tn = (TreeNode){val, 0, NULL, NULL};
    return tn;
}

typedef struct
{
	TreeNode* root;
} AVLTree;

AVLTree createAVLTree()
{
    return (AVLTree){NULL};
}

int height(TreeNode* node)
{
	return node == NULL ? -1 : node->height;
}

int getHeight(TreeNode* root)
{
	if(root == NULL) return 0;

	int lh = getHeight(root->left);
	int rh = getHeight(root->right);

	return (lh > rh) ? ++lh : ++rh;
}

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

TreeNode* doubleRotateRight(TreeNode* a)
{
	a->right = rotateRight(a->right);
	return rotateLeft(a);
}

TreeNode* doubleRotateLeft(TreeNode* a)
{
	a->left = rotateLeft(a->left);
	return rotateRight(a);
}

TreeNode* balance(TreeNode* node)
{
	if(height(node->left) - height(node->right) > 1)
	{
		if(height(node->left->left) >= height(node->left->right)) node = rotateRight(node);
			/*
				case 1: long left node
					 a            b
					/            / \
				   b   -->      c   a
	              /
				 c
			*/
		else node = doubleRotateLeft(node);
			/*
				case 2: double left
				  a              a             c
				 /              /             / \  
				b     -->      c      -->    b   a
				 \            /                 
				  c          b                 
			*/
	}

	if(height(node->right) - height(node->left) > 1)
	{
		if(height(node->right->right) >= height(node->right->left)) node = rotateLeft(node);
			/*
			   case 3: long right node
			   a               b
				\             / \
				 b    -->    a   c
				  \
				   c
			*/
		else node = doubleRotateLeft(node);
			/*
				case 4: double rotate left
				a               a              c
				 \               \            / \  
				  b  -->          c   -->    b   a
				 /                 \           
				 c                  b        
			*/
	}

	// update root height
	node->height = (height(node->left) > height(node->right)) ? height(node->left) + 1: height(node->right) + 1;
	return node;
}

TreeNode* addTreeNode(TreeNode* root, int val)
{
	// base case, finding position of new node or tree is empty
	if(root == NULL) return createTreeNode(val);

	// recursivley find the correct pos of the passed value
	if(root->val < val) root->right = addTreeNode(root->right, val);
	else if(root->val > val) root->left = addTreeNode(root->left, val);

    // balance the nodes at each traversal
    return balance(root);
}

TreeNode* sucessor(TreeNode* root)
{
	TreeNode* tn = root->right;
	while(tn->left != NULL) tn = tn->left;
	return tn;
}

TreeNode* deleteTreeNode(TreeNode* root, int val)
{
	// the value does not exist in the tree
	if(root == NULL) return NULL;

    // finding the node
	if(root->val > val) root->left = deleteTreeNode(root->left, val);
	else if(root->val < val) root->right = deleteTreeNode(root->right, val);

	// found the node to delete
	else
	{
        bool hl = (root->left != NULL);
        bool hr = (root->right != NULL);
		
        // case 1: no children
		if(!hr && !hl) {free(root);return NULL;}

		// case 2: right child
		else if(hr && !hl)
		{
			TreeNode* tn = root->right;
			free(root);
			return tn;
		}

		// case 3: left child
		else if(hl && !hr)
		{
			TreeNode* tn = root->left;
			free(root);
			return tn;
		}

        // case 4: 2 children, return smallest node in right subtree
		else
		{
			TreeNode* tn = sucessor(root);

			// replace delNodes value
			root->val = tn->val;

			// delete duplicate, is either a child of right node or is right node itself
			root->right = deleteTreeNode(root->right, tn->val);
		}
	}

	return balance(root);
}

void printAVLTree(TreeNode* root)
{
	if(root == NULL) return;

	printAVLTree(root->left);
	printf("Node: %d  Height: %d\n", root->val, root->height);
	printAVLTree(root->right);
}

void deleteAVLTree(AVLTree* AVLTree)
{
	while(AVLTree->root != NULL) AVLTree->root = deleteTreeNode(AVLTree->root, AVLTree->root->val);
}

int main()
{
    ArrayList al = createArrayList();
    LinkedList ll = createLinkedList();
    Stack st = createStack();
    Queue q = createQueue();
    AVLTree avl = createAVLTree();

    for(int i = 0; i < CAP; i++)
    {
        addElement(&al, i);
        addBack(&ll, i);
        push(&st, i);
        offer(&q, i);
        avl.root = addTreeNode(avl.root, i);
    }

    printArrayList(&al);
    printLinkedList(ll);
    printAVLTree(avl.root);

    deleteQueue(&q);
    deleteArrayList(&al);
    deleteLinkedList(&ll);
    deleteStack(&st);
    deleteAVLTree(&avl);
    return 0;
}