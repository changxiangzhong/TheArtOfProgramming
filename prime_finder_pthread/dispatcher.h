#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <stdint.h>


typedef struct {
	// specify what value it is
	uint64_t current;

	// specify how many value to return
	uint32_t pace;

	// specify the boundry
	uint64_t end;
	
	// "Mutex will usually allow it to spin for a short time." --on a StackOverflow thread.
	// In this context, it seems true - when migrating to spinlock from mutex, I cannot observe an obvious performance
	// boost.
#ifdef _USE_SPINLOCK
	pthread_spinlock_t spinlock;
#else
	// mutex
	pthread_mutex_t mutex;
#endif

} task_queue;

typedef struct {
	uint64_t start;
	uint64_t len;
} range;

extern void tq_init(task_queue *this, uint64_t max, uint64_t min, uint32_t pace);

extern range tq_get_task(task_queue *this); 

extern void tq_destroy(task_queue *this);

#endif
