#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
 * Given an array a[size], put the odd number together to the head of the array, 
 * put the even number together to the tail of the array.
 */

int *a;
int size;

int main(int argc, char* argv[])
{
	int i, j, k, tmp;
	assert(argc >= 3);

	size = argc - 1;
	a = (int*) calloc(sizeof(int), size);

	for(i = 0; i < size; i++)
		a[i] = atoi(argv[i + 1]);

	i = 0; j = size - 1;
	while (i < j){
		// find the 1st even # from left
		while (a[i] % 2 == 1)
			if (++i >= j)
				goto finished;

		// find the 1st odd # from right
		while (a[j] % 2 == 0)
			if (--j <= i)
				goto finished;
		
		tmp = a[i];
		a[i++] = a[j];
		a[j--] = tmp;
	}

finished:

	for (k = 0; k < size; k++)
		printf("%d, ", a[k]);

	return 1;
}
