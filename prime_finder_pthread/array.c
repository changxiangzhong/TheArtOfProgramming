#include <stdlib.h>
#include <assert.h>
#include "array.h"

void array_init(array * const this, uint32_t capacity)
{
	this->array = calloc(sizeof(uint64_t), capacity);
	this->capacity = capacity;
	this->len = 0;
	pthread_mutex_init(&this->mutex, NULL);
}

void array_append(array * const this, uint64_t to_append)
{
	assert(this->len < this->capacity);

	pthread_mutex_lock(&this->mutex);
	this->array[this->len] = to_append;
	this->len++;
	pthread_mutex_unlock(&this->mutex);
}

void array_destroy(array * const this)
{
	pthread_mutex_destroy(&this->mutex);
	free(this->array);
}
