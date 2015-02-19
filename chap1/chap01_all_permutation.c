#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

void swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void calc_all_permutation(char * const s, int from, int to)
{
	int i;
	if (from == to)
		printf("%s\n", s);

	for (i = from; i < to; i++) {
		swap(s + from, s + i);
		calc_all_permutation(s, from + 1, to);
		swap(s + i, s + from);
	}
		
}

int main(int argc, char* argv[])
{
	assert(argc == 2);
	calc_all_permutation(argv[1], 0, strlen((argv[1])));
}
