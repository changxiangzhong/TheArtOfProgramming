#include <stdlib.h>
#include <assert.h>
#include "array.h"

void array_init(array * const this, uint32_t capacity)
{
	this->array = calloc(sizeof(uint64_t), capacity);
	this->capacity = capacity;
	this->len = 0;
}

void array_append(array * const this, uint64_t to_append)
{
	assert(this->len < this->capacity);
	this->array[this->len] = to_append;
	this->len++;
}

void array_destroy(array * const this)
{
	free(this->array);
}
