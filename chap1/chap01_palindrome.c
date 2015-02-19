#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

int is_palindrome(const char *s, int n){
	int i = 0;
	int j = n - 1;
	while (i < j) {
		if (s[i] != s[j]) {
			return 0;
		}
		i++;
		j--;
	}

	return 1;
}



int main(int argc, char* argv[])
{
	assert(argc == 2);
	int result = is_palindrome(argv[1], strlen(argv[1]));
	printf("The input is %s palindrome string\n", result? "": "not");
}
