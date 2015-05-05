
#include "dispatcher.h"
#include "util.h"


void tq_init(task_queue *this, uint64_t max, uint64_t min, uint32_t pace)
{
	this->current = max;
	this->end = min;
	this->pace = pace;
#ifdef _USE_SPINLOCK
	pthread_spin_init(&this->spinlock, PTHREAD_PROCESS_PRIVATE);
#else
	pthread_mutex_init(&this->mutex, NULL);
#endif
}

range tq_get_task(task_queue *this)
{
	range r;
#ifdef _USE_SPINLOCK
	pthread_spin_lock(&this->spinlock);
#else
	pthread_mutex_lock(&this->mutex);
#endif
	r.start = this->current;
	r.len = this->current > this->end + this->pace? this->pace: this->current - this->end;
	this->current -= r.len;
#ifdef _USE_SPINLOCK
	pthread_spin_unlock(&this->spinlock);
#else
	pthread_mutex_unlock(&this->mutex);
#endif
	return r;
}

void tq_destroy(task_queue *this)
{
#ifdef _USE_SPINLOCK
	pthread_spin_destroy(&this->spinlock);
#else
	pthread_mutex_destroy(&this->mutex);
#endif
}
