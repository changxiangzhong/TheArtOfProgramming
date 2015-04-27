#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binary_tree.h"


int main(int argc, char *argv[])
{
	int i;
	assert(argc > 1);

	int *val = calloc(sizeof(int), (size_t)argc - 1);
	for (i = 0; i < argc - 1; i++)
		val[i] = atoi(argv[i+1]);

	bt_node* root = bt_comp_tree_init(argc - 1, val);
	bt_tree_print(root, (char * const)"");
	printf("This tree is %sa Binary Search Tree\n", bt_tree_is_BST(root)?"":"NOT ");

	int *buff = calloc(sizeof(int), (unsigned) 30);

	bt_tree_in_order_traverse(root, buff, 30);

	for (i = 0; i < 30; i++) {
		if(buff[i] == 0)
			break;
		printf("%d", buff[i]);
	}

	free(buff);


	bt_tree_destroy(root);
	free(val);
	return 1;
}

