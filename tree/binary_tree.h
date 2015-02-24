#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdbool.h>

#define debug_printf(fmt, ...) \
	do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
		__LINE__, __func__, ##__VA_ARGS__); } while (0)
/*
 * bt_node stands for binary tree node
 */
struct bt_node 
{
	int *value;
	struct bt_node *left;
	struct bt_node *right;

};

typedef struct bt_node bt_node;

extern void bt_node_init(bt_node* const this, int value, bt_node* const left, bt_node* const right);
extern void bt_node_destroy(bt_node* const this);
/*
 * Note! this method is to construct a complete binary tree!
 */
extern bt_node* bt_comp_tree_init(const int len, const int *const values);
extern void bt_tree_print(const bt_node * const root, char * const prefix, bool is_tail);
extern void bt_tree_destroy(const bt_node* root);
/*
 * To determine if the tree is a binary search tree
 */
extern bool bt_tree_is_BST(const bt_node * const root);

#endif

