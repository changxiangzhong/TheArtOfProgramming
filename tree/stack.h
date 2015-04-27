#ifndef __STACK_H__
#define __STACK_H__

#include<stdbool.h>

typedef struct {
	int cap;
	int len;
	int *data;
} stack;

extern bool stack_init(stack * const this, int cap);

extern void stack_destroy(stack * const this);

extern bool stack_push(stack * const this, const int value);

extern int stack_pop(stack * const this);

#endif

