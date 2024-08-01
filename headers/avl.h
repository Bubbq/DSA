#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
	int val;
	int height;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;

TreeNode* create_tree_node(int val);

typedef struct
{
	TreeNode* root;
} AVLTree;

AVLTree create_avl_tree();
int height(TreeNode* node);
TreeNode* rotate_right(TreeNode* a);
TreeNode* rotate_left(TreeNode* a);
TreeNode* double_rotate_right(TreeNode* a);
TreeNode* double_rotate_left(TreeNode* a);
TreeNode* balance_avl_tree(TreeNode* node);
TreeNode* add_tree_node(TreeNode* root, int val);
TreeNode* get_successor(TreeNode* root);
void dealloc_avl_tree(AVLTree* root);
TreeNode* delete_tree_node(TreeNode* root, int val);
void inorder_avl_tree_traversal(TreeNode* root);

#endif