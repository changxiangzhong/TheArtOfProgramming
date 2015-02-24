#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "binary_tree.h"

inline static bool _is_leaf(const bt_node *const this)
{
	return this->left == NULL && this->right == NULL;
}

inline static bool _left_child_of(const bt_node *this, const bt_node *ancestor)
{
	assert(this != NULL && ancestor != NULL);
	if (ancestor->left == this)
		return true;
	else if (ancestor->right == this)
		return false;
	else 
		assert(0);
}
/* 
 * In general, constructor should be responsible for 
 * 1. allocate/new heap space for "value pointers"
 * 2. assign default value
 */
void bt_node_init(bt_node* const this, int value, bt_node* const left, bt_node* const right)
{
	assert(this != NULL);
	this->right = left;
	this->left = right;
	this->value = malloc(sizeof(int));
	*(this->value) = value;
}

/* 
 * In comparison, destructor should be responsible for 
 * 1. deallocate heap space for "value pointers"
 */
void bt_node_destroy(bt_node* const this)
{
	assert(this != NULL && "");
	free(this->value);
}

/*
 * Initialize a 'complete tree' with the given values in an array. In a binary tree, each level could accommodate 2^n 
 * of elements. To calculate the position of a N'th element(array start from 0). For any N>0
 * 	2^0 + 2^1 + ... 2^n <= N < 2^0 + ... 2^(n+1) 
 * 	==> 2^(n+1) - 1 <= N < 2^(n+2) - 1
 * 	==> 2^(n+1) <= N+1 < 2^(n+2)
 *
 *	Conclusion: for N'th element in an array start from 0
 *		X = floor(log2(N + 1))
 *		Y = N - 2^X + 1
 *	
 *	Conclusion: for N'th element in an array start from 0,
 *		its children are 2 * N + 1, 2 * N + 2
 *
 *	For any node at (X, Y), it's child node will locate at (X+1, 2*Y) and (X+1, 2*Y+1)
 *	For a given node at (X, Y), it's index in the array should be (2^X + Y - 1)
 */
bt_node* bt_comp_tree_init(const int len, const int *const values)
{
#define L_CHILD(n) (2 * (n) + 1)
#define R_CHILD(n) (2 * (n) + 2)
	int i;
	bt_node *root;
	bt_node **buf = (bt_node**) calloc(sizeof(bt_node*), (size_t)len);
	// very bad idea! For C we can only recycle the bulk of memory. We cannot partially recycle a bulk. And the
	// caller does not have the memory of how the memory is organized!
	// 	root = calloc(sizeof(bt_node), (size_t)len);
	// cannot free(root + 1);
	//
	// So the best alternative would be to allocate heap for each node one by one.
	
	for (i = 0; i < len; i++)
	{
		buf[i] = malloc(sizeof(bt_node));
		bt_node_init(buf[i], values[i], NULL, NULL);
	}

	root = buf[0];

	for (i = 0; i < len; i++)
	{
		if (L_CHILD(i) >= len)
			continue;
		else
			buf[i]->left = buf[L_CHILD(i)];

		if (R_CHILD(i) >= len)
			continue;
		else
			buf[i]->right = buf[R_CHILD(i)];
	}
	free(buf);
	return root;
}

void bt_tree_destroy(const bt_node* this)
{
	if (this -> left != NULL)
		bt_tree_destroy(this -> left);

	if (this -> right != NULL)
		bt_tree_destroy(this -> right);

	free(this->value);
	free((void*)this);
}

/*
 * @this - which subtree we are investigating
 * @ancestor - the ancestor of this
 */
bool _bt_tree_is_BST(const bt_node * const this, const bt_node * const ancestor)
{
	bool ret = true;
	assert(this != NULL);

	debug_printf("ancestor->value=%d, this->value = %d, this->left->value = %d, this->right->value = %d\n", 
				ancestor==NULL? -1: *ancestor->value,
				*this->value, 
				this->left == NULL? -1: *this->left->value,
				this->right == NULL? -1: *this->right->value);

	if (this->left != NULL) {
		if (*this->left->value < *this->value) {
			if (!_is_leaf(this->left)) {
				ret = _bt_tree_is_BST(this->left, this);
			}
		} else {
			ret = false;
			debug_printf("left.value >= this.value\n");
		}

		 
		/* 		(5)		<--ancestor
		 * 		  \
		 * 		  (13)	<--this
		 * 		   /
		 * 		 (4)
		 */
		if (ancestor != NULL && !_left_child_of(this, ancestor)) {
			if (*ancestor->value > *this->left->value) {
				ret = false;
				debug_printf("\n(%d)\n  \\\n  (%d)\n   /\n (%d)\n",
						*ancestor->value,
						*this->value,
						*this->left->value);
			}
		}

	}

	if (!ret)
		return ret;

	if (this->right != NULL) {
		if (*this->right->value > *this->value) {
			if (!_is_leaf(this->right)) {
				ret = _bt_tree_is_BST(this->right, this);
			}
		} else {
			ret = false;
			debug_printf("right.value <= this.value\n");
		}
		/* 		(5)		<--ancestor
		 *		/
		 * 	  (3)		<--this
		 * 	    \
		 * 	    (6)
		 */
		if (ancestor != NULL && _left_child_of(this, ancestor)) {
			if(*this->right->value > *ancestor->value) {
				ret = false;
				debug_printf("\n  (%d)\n /\n(%d)\n \\\n (%d)\n",
						*ancestor->value,
						*this->value,
						*this->right->value);
			}
		}
	}
	return ret;
}


/*
 * Must take the following case into consideration
 * A)		(5)
 * 			/
 * 		  (3)
 * 		    \
 * 		    (6)
 *
 * B)
 *  		(5)
 *  		  \
 *  		  (13)
 *  		   /
 *  		 (4)
 */
bool bt_tree_is_BST(const bt_node * const this)
{
	return _bt_tree_is_BST(this, NULL);
}

/*
 * Modified from http://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram/8948691#8948691
 * Adapted from Vasya Novikov's solution
 */
static void _bt_tree_print(const bt_node * const this, char * const prefix, bool is_tail)
{
	char *buf; 
	assert(this != NULL);
	printf("%s%s%d\n", prefix, is_tail? "└── " : "├── ", *this -> value);

	buf = calloc(sizeof(char), (size_t)strlen(prefix) + 1 + 4);
	strncpy(buf, prefix, strlen(prefix));
	strncpy(buf + strlen(buf), (is_tail ? "    " : "│   "), 4);
	if (this->left != NULL) 
		_bt_tree_print(this->left, buf, false); 
	

	if (this->right != NULL) 
		_bt_tree_print(this->right, buf, true);

	free(buf);	
	
}

void bt_tree_print(const bt_node * const this, char * const prefix)
{
	_bt_tree_print(this, prefix, true);
}
