#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


void n_sum(int n, int sum) {
	int i = 1;
	for (i; sum - n > 0; i++) {
		printf("%d, ", i);
	}
}

int main(int argc, char* argv[])
{
	assert(argc == 3);
	
	n = atoi(argv[1]);
	sum = atoi(argv[2]);


}
