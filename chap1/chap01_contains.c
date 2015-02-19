#include <stdio.h>
#include <string.h>

int contains(char *const a, const int n, char *const b, const int m)
{
	int i,j;
	for (i = 0; i < n - m + 1; i++) {
		for (j = 0; j < m; j++) {
			if (a[i + j] != b[j])
				break;
		}

		if (j == m)
			return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	char *container = argv[1];
	char *containee = argv[2];
	printf("Container=%s, sizeof(Container) = %d, Containee=%s, sizeof(Containee)=%d\n", container, strlen(container), containee, strlen(containee));
	if(contains(container, strlen(container), containee, strlen(containee)))
		printf("Contains!\n");
	else
		printf("Not Contains!\n");
}
