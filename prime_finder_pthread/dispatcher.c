
#include "dispatcher.h"
#include "util.h"


void tq_init(task_queue *this, uint64_t max, uint64_t min, uint32_t pace)
{
	this->current = max;
	this->end = min;
	this->pace = pace;
	pthread_mutex_init(&this->mutex, NULL);
}

range tq_get_task(task_queue *this)
{
	range r;
	pthread_mutex_lock(&this->mutex);
	r.start = this->current;
	r.len = this->current - this->pace > this->end ? this->pace: this->current - this->pace;
	this->current -= r.len;
	pthread_mutex_unlock(&this->mutex);
	return r;
}
