#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

bool stack_init(stack * const this, int cap)
{
	assert(this != NULL);
	this->cap = cap;
	this->len = 0;
	this->data = calloc(sizeof(int), (size_t) cap);
	return this->data != NULL;
}

void stack_destroy(stack * const this)
{
	assert(this != NULL);
	free(this->data);
}

bool stack_push(stack * const this, const int value)
{
#define STACK_INCREMENTAL_FACTOR 2
	int *temp;
	assert(this != NULL);

	if (this->len >= this->cap) {
		temp = calloc(sizeof(int), (size_t) (this->cap * STACK_INCREMENTAL_FACTOR));

		// calloc failure
		if (!temp)
			return false;
		
		this->cap = this->cap * STACK_INCREMENTAL_FACTOR;
		memcpy(temp, this->data, (unsigned)this->len * sizeof(int));
		free(this->data);
		this->data = temp;
	}


	this->data[this->len++] = value;
	return true;
}

int stack_pop(stack * const this)
{
	assert(this != NULL);
	int to_ret;
	if(this->len - 1 < 0)
		return -1;

	to_ret = this->data[this->len - 1];
	this->len --;
	return to_ret;
}

