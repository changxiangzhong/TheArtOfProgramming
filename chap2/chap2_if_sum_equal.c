#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Given A[n] check if exist A[i] + A[j]... + A[z] == k
 *
 * Let function f(i, k) - if a composition (containing i elements) exists to satisfy 
 * A[i1] + A[i2] +... A[ii] == k
 *
 * f(i, k) = f(i - 1, k) || f(i - 1, k - A[i])
 */

int *a;
int size;

int *idx;
int len;

// To save a len variable, we use backward iteration
//
int if_comp_exist(int i, int k) {
	printf("==>i=%d, k=%d\n", i, k);
	if (i < 0 || k < 0)
		return 0;
	if (a[i] == k) {
		int j = 0;
		idx[len++] = i;
		for(; j < len; j++)
			printf("a[%d] + ", idx[j]);
		printf(" == result\n");
		len--;
		return 1;
	}

	int without_i = if_comp_exist(i - 1, k);
	if (without_i)
		return 1;

	idx[len++] = i;
	int with_i = if_comp_exist(i - 1, k - a[i]);
	len--;
	return with_i;
}

int main(int argc, char* argv[])
{
	assert(argc > 3);
	// a[] = { argv[1], argv[2],...,argv[argc - 2]}
	// k = argv[argc - 1]
	int k = atoi(argv[argc - 1]);
	printf("k = %d\n", k);
	int i;

	size = argc - 2;
	a = (int*) calloc(sizeof(int), size);
	for (i = 0; i < size; i++) {
		a[i] = atoi(argv[i + 1]);
		printf("a[%d]=%d, ", i, a[i]);
	}
	printf("\n");

	idx = (int*) calloc(sizeof(int), size);
	len = 0;

	if_comp_exist(size - 1, k); 

}
