#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define min(X,Y) ((X)<(Y)?(X):(Y))

int find_longest_palindrome(const char *s, int n){
	int max = 0;
	int i, j, k;
	int record;

	// TODO: handle case i = j;
	for (i = 0; i < n; i++) {
		j = i + 1;
		if (j >= n)
			break;
	
		record = 0;
		// calculate the max range
		for (k = 0; k < min(i - 0 + 1, n - 1 - j + 1); k++) {
			if (s[i-k] == s[j+k])
				record++;
			else
				break;
		}

		max = record > max? record: max;
		
		
		j = i;
		if (j >= n)
			break;
	
		record = 0;
		// calculate the max range
		for (k = 1; k < min(i - 0 + 1, n - 1 - j + 1); k++) {
			if (s[i-k] == s[j+k])
				record++;
			else
				break;
		}

		max = record > max? record: max;
	}
	return max;
}



int main(int argc, char* argv[])
{
	assert(argc == 2);
	int result = find_longest_palindrome(argv[1], strlen(argv[1]));
	printf("length of the longest palindrome string is %d\n", result);
}
