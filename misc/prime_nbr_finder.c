#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>

typedef struct {
	uint64_t *array;
	uint32_t len;
} ll_array;

#define ARRAY_CAPACITY 1<<20

void ll_array_init(ll_array * const this)
{
	printf("ARRAY_LEN_MAX=%u\n", ARRAY_CAPACITY);
	this->array = calloc(sizeof(uint64_t), ARRAY_CAPACITY);
	this->len = 0;
}

void ll_array_append(ll_array * const this, uint64_t to_append)
{
	//	printf("this->len=%d", this->len);
	this->array[this->len] = to_append;
	//	printf("\t%lld\n", this->array[this->len]);
	this->len++;
}

void ll_array_destroy(ll_array * const this)
{
	free(this->array);
}

void init_known_prime_list(ll_array * const this) 
{
	uint64_t known_primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
	int i = 0;
	for(; i < sizeof (known_primes)/sizeof(uint64_t); i++)
		ll_array_append(this, known_primes[i]);
}

char* get_time()
{   
	time_t now;
	struct tm ts;
	static char buf[80];
	// Get current time
	time(&now);
	// Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
	ts = *localtime(&now);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
	return buf;
}

void calculate_prime_list(ll_array * const arr)
{
	int i;
	uint64_t last_known;
	uint64_t iter = arr -> array[arr->len - 1];
	iter += 2;
	while (iter < UINT64_MAX && arr->len < ARRAY_CAPACITY)
	{
		if (iter % 10000 == 1)
			printf("scanned to %lld at %s, last known prime: %lld, found %u prime nbr\n", 
					iter, 
					get_time(), 
					last_known,
					arr->len
					);
		for (i = 0; i < arr->len; i++)
		{
			if(iter % arr->array[i] == 0)
				break;
		}

		if (i == arr->len) {
			ll_array_append(arr, iter);
			last_known = iter;
		}

		iter+=2;
	}

	printf("Biggest prime number found: %lld\n", last_known);
}

int main(int argc, char* argv[])
{
	ll_array arr;
	ll_array_init(&arr);

	init_known_prime_list(&arr);
	calculate_prime_list(&arr);

	ll_array_destroy(&arr);
	return 1;
}
