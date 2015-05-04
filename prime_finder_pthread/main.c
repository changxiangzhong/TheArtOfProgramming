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

static void find_prime_nbr(uint64_t min, uint64_t max, array * const ret)
{
	uint64_t iter = max;

	util_printf("Finding range (%" PRIu64 ", %" PRIu64 "] \n", min, max);

	while (iter > min) {
		uint64_t sqrt_max = (uint64_t) sqrt(iter) + 1;
		uint64_t i;
	
		for(i = 2; i < sqrt_max; i++) {	
			if (iter % i == 0)
				break;	
		}

		if (i == sqrt_max) {
			util_printf("Found prime number: %" PRIu64 "\n", iter);
//			array_append(ret, iter);
		} else 
			;

		iter%2? iter-=2: iter--;
	}

	util_printf("%s", "===> Cycle done.\n" );

}

static void* worker_thread(void* param)
{
	task_queue *tq = (task_queue*)param;
	range r;
	r.len = 1;
	util_printf("%s", "Thread started!\n");
	while(true) {
		r = tq_get_task(tq);
		if (r.len <= 0)
			break;
//		util_printf("Get task from (%" PRIu64 ", %" PRIu64 "]\n", r.start - r.len, r.start );
		find_prime_nbr(r.start - r.len, r.start, NULL);
		sleep(1);
	};

	return NULL;
}


int main(int argc, char* argv[])
{
	int i;
	uint8_t cpu_nbr = (uint8_t) sysconf(_SC_NPROCESSORS_ONLN);
	task_queue tq;
	uint64_t start = UINT64_MAX, end = UINT64_MAX - 1024;
	uint32_t pace = 100;

	printf("argc == %d\n", argc);

	if (argc == 4) {	
		sscanf(argv[1], "%" PRIu64, &start);
		sscanf(argv[2], "%" PRIu64, &end);
		sscanf(argv[3], "%" PRIu32, &pace);
	}

	pthread_t workers[cpu_nbr];

	tq_init(&tq, start, end, pace);
	
	for (i = 0; i < cpu_nbr; i++) {

		if (pthread_create(workers + i, NULL, worker_thread, &tq)) {
			util_printf("%s", "Error returned when creating a thread\n");
			exit(EXIT_FAILURE);
		}

	}

	for (i = 0; i < cpu_nbr; i++) 
		pthread_join(workers[i], NULL);

	return 0;
}
