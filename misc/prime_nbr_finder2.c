#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#define __STDC_FORMAT_MACROS

int main(int argc, char* argv[])
{
	uint64_t iter = UINT64_MAX;
	
	if (argc == 2) 
		iter = sprintf(argv[1], "%" PRIu64, iter);

	printf("Ceiling is: %" PRIu64 "\n", iter);

	while (iter > 0) {
		uint64_t max = sqrt(iter) + 1;
		uint64_t i;
	
		for(i = 2; i < max; i++) {	
			if (iter % i == 0)
				break;	
		}

		if (i == max)
			break;

		iter%2? iter-=2: iter--;
		printf("%" PRIu64 " is not a prime number\n", iter);
	}

	if (iter > 0)
		printf("Max prime number found: %" PRIu64 "\n", iter);

	return 1;
}
