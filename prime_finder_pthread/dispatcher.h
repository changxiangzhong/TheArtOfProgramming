#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <pthread.h>
#include <stdint.h>


typedef struct {
	// specify what value it is
	uint64_t current;

	// specify how many value to return
	uint32_t pace;

	// specify the boundry
	uint64_t end;

	// mutex
	pthread_mutex_t mutex;
} task_queue;

typedef struct {
	uint64_t start;
	uint64_t len;
} range;

extern void tq_init(task_queue *this, uint64_t max, uint64_t min, uint32_t pace);

extern range tq_get_task(task_queue *this); 

#endif
