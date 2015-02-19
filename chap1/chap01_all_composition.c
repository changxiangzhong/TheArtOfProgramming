#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char* set;

void calc_combination(char * const s, int offset, int len) 
{
	int i = 0;
	if (offset == len) {
		printf("==>%s\n", s);
		return;
	}

	for (; i < strlen(set); i++) {
		s[offset] = set[i];
		calc_combination(s, offset + 1, len);
	}
}

int main(int argc, char* argv[])
{
	assert(argc == 3);
	// suppose the input is ordered
	int i = 0;
	set = argv[1];
	int selected = atoi(argv[2]);
	assert(selected <= strlen(set));

	char* buf = (char*) calloc(sizeof (char), selected + 1);
	

	for (i = 1; i < selected + 1; i++) {
		calc_combination(buf, 0, i);
	}

	free(buf);
}
