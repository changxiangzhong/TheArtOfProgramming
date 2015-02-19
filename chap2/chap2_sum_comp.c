#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int* arr;
int len;

void sum_of_n(int sum, int n) {
	if (sum < 0 || n < 0)
		return;

	if (sum == n) {
		arr[len++] = n;
		int i = 0;
		printf("==>");
		for (; i < len; i++)
			printf("%d, ", arr[i]);
		printf("\n");
		len--;
	} else {
		// put the number n
		arr[len++] = n;
		sum_of_n(sum - n, n - 1);
		len--;
		sum_of_n(sum, n - 1);
	}
}

int main(int argc, char* argv[])
{
	assert(argc == 3);
	int sum = atoi(argv[1]);
	int n = atoi(argv[2]);
	assert(sum > n);
	// arr[sum] is more than enough
	arr = (int*) calloc(sizeof(int), sum);
	len = 0;
	sum_of_n(sum, n);
}
