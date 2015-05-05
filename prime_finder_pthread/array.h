#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <stdint.h>
#include <pthread.h>

typedef struct 
{
	uint64_t *array;
	uint32_t len;
	uint32_t capacity;
	pthread_mutex_t mutex;
} array;

extern void array_init(array * const this, uint32_t capacity);
extern void array_append(array * const this, uint64_t to_append);
extern void array_destroy(array * const this);

#endif

