#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Given an integer arr[n], which contains negative an positive value.
 * Among the sub arraies, find the maximum sum of the sub arries
 *
 * Requirement: O(T) = n;
 */

// Step 1: merge the array to have the following {+, -, +, -...} or {-, +, -, +...}
// Step 2: suppose the values are {-, +, -,...+, -}. Ignore the minus value at the begin and at the end. Because we are

// Suppose the array is processed in ways mentioned in step 1 & 2. So they are supposed to be {+, -, +, -... +}
int main(int argc, char* argv[])
{
	assert(argc > 3);
	int *a;
	int size;
	int i;
	size = argc - 1;
	a = (int*) calloc(sizeof(int), size);
	for (i = 0; i < size; i++) {
		a[i] = atoi(argv[i + 1]);
	}

	int left = 0;
	int record = a[left];
	for (i = 2; i < size; i += 2) {
		int tmp = record + a[i - 1] + a[i];
		if(tmp > record) {
			left = i;
		   	record = tmp;	
		}
	}

	int right = size - 1;
	record = a[right];
	for (i = size - 3; i >= 0; i -= 2) {
		int tmp = record + a[i] + a[i + 1];
		if (tmp > record) {
			right = i;
			record = tmp;
		}
	}

	printf("from=%d, to=%d is the sub string with max sum\n", right, left);
}
