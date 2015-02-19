#include <stdio.h>
#include <string.h>

void reverse(char* const a, const int n, const int k)
{
	int i = 0;
	int tmp = 0;
	for (; i < n - k; i++) {
		tmp = a[i];
		a[i] = a[i + k];
		a[i + k] = tmp;
	}
}	

int main(int argc, char* argv[])
{
	char toReverse[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'};
	printf("before reverse: %s\n", toReverse);
	reverse(toReverse, strlen(toReverse), 3);
	printf("after reverse: %s\n", toReverse);
}
