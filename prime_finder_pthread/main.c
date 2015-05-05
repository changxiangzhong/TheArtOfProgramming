#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "dispatcher.h"
#include "util.h"
#include "array.h"

typedef struct{
	task_queue *tq;
	array *result;
}thread_params;

// Based upon Dusart 99, calculate the upper bound of the prime number amount in range [min, max]
static uint32_t estimate_prime_nbr_amount(uint64_t min, uint64_t max)
{
	// range0: [0, max], range1: [0, min}
	double range0, range1;
	assert(min < max);

	range0 = ceil(max/log(max) * (1 + 1.2762/log(max)));
	range1 = floor(max/log(min) * (1 + 1.2762/log(min)));

	return (uint32_t)(range0 - range1);
}

static void find_prime_nbr(uint64_t min, uint64_t max, array * const ret)
{
	uint64_t iter = max;

	min = min < 1?1:min;

//	util_printf("Finding range (%" PRIu64 ", %" PRIu64 "] \n", min, max);

	while (iter > min) {
		uint64_t sqrt_max = (uint64_t) sqrt(iter) + 1;
		uint64_t i;
	
		for(i = 2; i < sqrt_max; i++) {	
			if (iter % i == 0)
				break;	
		}

		if (i == sqrt_max) {
//			util_printf("Found prime number: %" PRIu64 "\n", iter);
			array_append(ret, iter);
		} else 
			;

		if (iter == 3) {
			iter--;
		} else {
			iter%2? iter-=2: iter--;
		}
	}

//	util_printf("===> (%" PRIu64 ", %" PRIu64 "] done.\n", min, max);

}

static void* worker_thread(void* param)
{
	thread_params *tp = (thread_params*) param;
	task_queue *tq = tp->tq;
	array *result = tp->result;
	range r;
	r.len = 1;
//	util_printf("%s", "Thread started!\n");
	while(true) {
		r = tq_get_task(tq);
		if (r.len <= 0)
			break;
//		util_printf("Get task from (%" PRIu64 ", %" PRIu64 "]\n", r.start - r.len, r.start );
		find_prime_nbr(r.start - r.len, r.start, result);
		sleep(1);
	};

	return NULL;
}


int main(int argc, char* argv[])
{
	uint32_t i;
	uint32_t cpu_nbr = (uint8_t) sysconf(_SC_NPROCESSORS_ONLN);
	uint64_t start = UINT64_MAX, end = UINT64_MAX - 100;
	uint32_t pace = 10;
	uint32_t prime_nbr_count;
	thread_params tp;
	
	task_queue tq;
	array result;

	if (argc == 5) {
		sscanf(argv[1], "%" PRIu64, &start);
		sscanf(argv[2], "%" PRIu64, &end);
		sscanf(argv[3], "%" PRIu32, &pace);
		sscanf(argv[4], "%" PRIu32, &cpu_nbr);
	}

	util_printf("start=%" PRIu64 ", end=%" PRIu64 ", pace=%" PRIu32 ", threads=%" PRIu32 "\n", start, end, pace, cpu_nbr);
	
	prime_nbr_count = estimate_prime_nbr_amount(end, start);
	array_init(&result, prime_nbr_count);

	pthread_t workers[cpu_nbr];

	tq_init(&tq, start, end, pace);
	
	tp.result = &result;
	tp.tq = &tq;
	
	for (i = 0; i < cpu_nbr; i++) {

		if (pthread_create(workers + i, NULL, worker_thread, &tp)) {
			util_printf("%s", "Error returned when creating a thread\n");
			exit(EXIT_FAILURE);
		}

	}

	for (i = 0; i < cpu_nbr; i++) 
		pthread_join(workers[i], NULL);

	util_printf("%s", "All done, print result\n");

//	for (i = 0; i < result.len; i++)
//		printf("%" PRIu64 "\n", result.array[i]);

	tq_destroy(&tq);
	array_destroy(&result);
	return 0;
}
