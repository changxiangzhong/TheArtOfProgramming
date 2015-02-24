#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

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
extern void bt_tree_print(const bt_node * const root, char * const prefix, int is_tail);
extern void bt_tree_destroy(const bt_node* root);

#endif

