#include<stdio.h>
#include<stdlib.h>

#define N 4
#define K 4

int A[] = {1, 2, 100, 200};
int B[] = {3, 5, 200, 300};

/*
 * a0 + b0 < a0 + b1 <...< a0 + bn
 * a1 + b0 < a1 + b1 <...< a1 + bn
 * ...............................
 * ...............................
 * ...............................
 * an + b0 < an + b1 <...< an + bn
 */

int main(int argc, char* argv[])
{
	int *i = (int*) calloc(sizeof(int), N);
	int j = 0;
	int k;
	for (; j < K; j++) {
		int idx = 0;
		int min = A[0] + B[i[0]];
		for (k = 1; k < N; k++) {
			if (A[k] + B[i[k]] < min) {
				idx = k;
				min = A[k] + B[i[k]];
			}
		}
		printf("%d, ", min);
		i[idx] ++;
	}
	free(i);
}
