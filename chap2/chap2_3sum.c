#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void three_sum(const int const * arr, int len, int idx)
{
	int i = 0;
	int j = len - 1;
	while(i < j) {
		if (arr[idx] == arr[i] + arr[j]) {
			printf("===>arr[%d] + arr[%d] == arr[%d]\n", i, j, idx);
			(++i == idx)? i++: i;
			j = len - 1;
		} else if (arr[idx] > arr[i] + arr[j]) {
			(++i == idx)? i++: i;
		} else if (arr[idx] < arr[i] + arr[j]) {
			(--j == idx)? j--: i;
		}

	}
}

int main(int argc, char* argv[])
{
	assert(argc >= 1 + 3);
	int i;
	int len = argc - 1;
	int *arr = (int*) calloc(sizeof(int), argc - 1);

	for (i = 1; i < argc; i++) {
		arr[i - 1] = atoi(argv[i]);
	}

	for (i = 0; i < len; i++) {
		three_sum(arr, len, i);
	}

	free(arr);
}
