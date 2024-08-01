#include "headers/avl.h"
#include <stdbool.h>

TreeNode* create_tree_node(int val)
{
    TreeNode* tn = malloc(sizeof(TreeNode));
    *tn = (TreeNode){val, 0, NULL, NULL};
    return tn;
}

AVLTree create_avl_tree()
{ 
    AVLTree avl;

    avl.root = NULL;

    return avl;
}

int height(TreeNode* node)
{ 
    return node == NULL ? -1 : node->height; 
}

TreeNode* rotate_right(TreeNode* a)
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

TreeNode* rotate_left(TreeNode* a)
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

TreeNode* double_rotate_right(TreeNode* a)
{
	a->right = rotate_right(a->right);
	return rotate_left(a);
}

TreeNode* double_rotate_left(TreeNode* a)
{
	a->left = rotate_left(a->left);
	return rotate_right(a);
}

TreeNode* balance_avl_tree(TreeNode* node)
{
	if(height(node->left) - height(node->right) > 1)
	{
		if(height(node->left->left) >= height(node->left->right)) node = rotate_right(node);
			/*
				case 1: long left node
					 a            b
					/            / \
				   b   -->      c   a
	              /
				 c
			*/
		else node = double_rotate_left(node);
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
		if(height(node->right->right) >= height(node->right->left)) node = rotate_left(node);
			/*
			   case 3: long right node
			   a               b
				\             / \
				 b    -->    a   c
				  \
				   c
			*/
		else node = double_rotate_left(node);
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

TreeNode* add_tree_node(TreeNode* root, int val)
{
	// base case, finding position of new node or tree is empty
	if(root == NULL) 
        return create_tree_node(val);

	// recursivley find the correct pos of the passed value
	if(root->val < val) 
        root->right = add_tree_node(root->right, val);

	else if(root->val > val) 
        root->left = add_tree_node(root->left, val);

    // balance the nodes at each traversal
    return balance_avl_tree(root);
}

TreeNode* get_successor(TreeNode* root)
{
	TreeNode* tn = root->right;
	
    while(tn->left != NULL) 
        tn = tn->left;
	
    return tn;
}

TreeNode* delete_tree_node(TreeNode* root, int val)
{
	// the value does not exist in the tree
	if(root == NULL) 
        return NULL;

    // finding the node
	if(root->val > val) 
        root->left = delete_tree_node(root->left, val);

	else if(root->val < val)
     root->right = delete_tree_node(root->right, val);

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
			TreeNode* tn = get_successor(root);

			// replace delNodes value
			root->val = tn->val;

			// delete duplicate, is either a child of right node or is right node itself
			root->right = delete_tree_node(root->right, tn->val);
		}
	}

	return balance_avl_tree(root);
}

void dealloc_avl_tree(AVLTree* AVLTree)
{ 
	while(AVLTree->root != NULL) 
		AVLTree->root = delete_tree_node(AVLTree->root, AVLTree->root->val);
}

void inorder_avl_tree_traversal(TreeNode* root)
{
	if(root == NULL) 
		return;

	inorder_avl_tree_traversal(root->left);
	printf("Node: %d  Height: %d\n", root->val, root->height);
	inorder_avl_tree_traversal(root->right);
}