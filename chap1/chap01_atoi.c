#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define BASE 10

int strToInt(char *str)
{
	int len = strlen(str);
	int sum = 0;
	int i,j;

	int sign = 1;

	if (str[0] == '-') {
		str++;
		len--;
		sign = -1;
	} else if (str[0] == '+') {
		str++;
		len--;
	}

	for (i = 0; i < len; i++) {
		int base = sign;
		for (j = 0; j < len - i - 1; j++)
			base *= BASE;
		
			
		sum += (str[i] - '0') * base;
		
		// Since this is a positive value, the highest bit should be 0
		if (sign == 1 && sum >> (sizeof(int) * 8 - 1))
			return INT_MAX;

		// Since this is a negative value, the highest bit should be 1
		if (sign == -1 && !(sum >> (sizeof(int) * 8 - 1)))
			return INT_MIN;
	}

	return sum;
}

int main(int argc, char* argv[])
{
	assert(argc == 2);
	int intValue = strToInt(argv[1]);
	printf("The result is: %d\n", intValue);
}
