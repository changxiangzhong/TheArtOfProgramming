#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define N 3

// V for value
int V[N] = {20, 10, 12};

// C for cost
int C[N] = {5, 4, 3};

/*
 * Let d(i, c) to be the max value
 *	d(i, c) = max(
 *		d(i - 1, c),
 *		d(i - 1, c - C[i]) + V[i]
 *	)
 */
int knapsack_01(int i, int c) {
	if (i == 0) {
		c > C[i]? V[i]: 0;
	} else {
		int put = knapsack_01(i - 1, c);
		int nput = knapsack_01(i - 1, c - C[i]) + V[i];
		return put > nput? put: nput;
	}
}

int main(int argc, char* argv[])
{
	int capacity = 10;
	int n = 3;
	int result = knapsack_01(3, 10);
	printf("==>The result is %d\n", result);
}
