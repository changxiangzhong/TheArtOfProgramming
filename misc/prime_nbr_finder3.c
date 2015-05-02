#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#define __STDC_FORMAT_MACROS

typedef struct 
{
	uint64_t *array;
	uint32_t len;
	uint32_t capacity;
} cxz_array;

extern void cxz_array_init(cxz_array * const this, uint32_t capacity);
extern void cxz_array_append(cxz_array * const this, uint64_t to_append);
extern void cxz_array_destroy(cxz_array * const this);
extern void find_prime_nbr(uint64_t min, uint64_t max, cxz_array * const ret);

static char* get_time()
{   
	time_t now;
	struct tm ts;
	static char buf[16];
	// Get current time
	time(&now);
	ts = *localtime(&now);
	strftime(buf, sizeof(buf), "%I:%M:%S %p", &ts);
	return buf;
}

void cxz_array_init(cxz_array * const this, uint32_t capacity)
{
	this->array = calloc(sizeof(uint64_t), capacity);
	this->capacity = capacity;
	this->len = 0;
}

void cxz_array_append(cxz_array * const this, uint64_t to_append)
{
	assert(this->len < this->capacity);
	this->array[this->len] = to_append;
	this->len++;
}

void cxz_array_destroy(cxz_array * const this)
{
	free(this->array);
}

/*
 * Locate the prime number from [min, max)
 */
void find_prime_nbr(uint64_t min, uint64_t max, cxz_array * const ret)
{
	uint64_t iter = max - 1;

	printf("[Thread-%lu][%s]\tFinding range [%" PRIu64 ", %" PRIu64 ") \n", pthread_self(), get_time(),  min, max);

	while (iter >= min) {
		uint64_t sqrt_max = (uint64_t) sqrt(iter) + 1;
		uint64_t i;
	
		for(i = 2; i < sqrt_max; i++) {	
			if (iter % i == 0)
				break;	
		}

		if (i == sqrt_max) {
			printf("[Thread-%lu][%s]\tFound prime number: %" PRIu64 "\n", pthread_self(), get_time(), iter);
			cxz_array_append(ret, iter);
		} else 
			;//printf("[Thread-%lu][%s]\t%" PRIu64 " is not a prime number.\n", pthread_self(), get_time(), iter);

		iter%2? iter-=2: iter--;
	}

	printf("[Thread-%lu][%s]\t===> Done. \n", pthread_self(), get_time());

}

typedef struct
{
	uint64_t min;
	uint64_t max;
	cxz_array *ret;
}thread_param;

static void* thread_adapter(void* param)
{
	thread_param *real_param = (thread_param*)param;
	find_prime_nbr(real_param->min, real_param->max, real_param->ret);
	return NULL;
}

int main(int argc, char* argv[])
{
	uint32_t range = 100;
	uint32_t i;
	uint8_t cpu_nbr = (uint8_t) sysconf(_SC_NPROCESSORS_ONLN);
	pthread_t workers[cpu_nbr];
	cxz_array ret[cpu_nbr];
	thread_param tp[cpu_nbr];

	printf("===>%d processor(s) online\n", cpu_nbr);

	for (i = 0; i < cpu_nbr; i++) {
		cxz_array_init(ret + i, range/2);
		tp[i].min = UINT64_MAX - (i + 1) * range;
		tp[i].max = UINT64_MAX - i * range;
		tp[i].ret = ret + i;

		if (pthread_create(workers + i, NULL, thread_adapter, tp + i)) {
			printf("Error returned when creating a thread\n");
			exit(EXIT_FAILURE);
		}

	}

	for (i = 0; i < cpu_nbr; i++) 
		pthread_join(workers[i], NULL);

	printf("All done\n");

	for (i = 0; i < cpu_nbr; i++) {
		cxz_array_destroy(ret + i);
	}

//	free(workers);

	return 1;
}
