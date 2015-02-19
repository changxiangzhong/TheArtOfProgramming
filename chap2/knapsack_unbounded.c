#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define N 3

/*
 * V[i] = value of item i;
 * C[i] = cost of item i;
 * Suppose d(i, c) - max sum value of item ranged in [0, i] put into a knapsack sized c
 * 	d(i, c) = max {
 * 		d(i - 1, c),
 * 		d(i - 1, c - 1 * C[i]) + 1 * V[i],
 * 		d(i - 1, c - 2 * C[i]) + 2 * V[i],
 * 		.................................
 * 		d(i - 1, c - k * C[i]) + k * V[i],
 * 	}
 *
 * 	where k * C[i] < j
 */

int V[N] = {20, 10, 12};
int C[N] = {5, 4, 3};

int knapsack_problem(int i, int c) {
	printf("==>i=%d, c=%d\n", i, c);
	int k = c / C[i];
	
	if (i == 0)
		return k * V[i];

	int record = 0;
	for (; k >= 0; k--) {
		int	tmp = knapsack_problem(i - 1, c - k * C[i]) + k * V[i];
		record = tmp > record? tmp: record;
	}

	return record;
}

int main(int argc, char* argv[])
{
	int capacity = 12;
	int n = 2;
	int result = knapsack_problem(n, capacity);
	printf("==>The result is %d\n", result);
}
