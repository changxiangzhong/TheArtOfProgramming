#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>

#include "util.h"

#define TIME_BUF 16

char* get_time()
{
	time_t now;
	struct tm ts;
	// keep it thread-safe
	static __thread char buf[TIME_BUF];
	// Get current time
	time(&now);
	ts = *localtime(&now);
	strftime(buf, sizeof(buf), "%H:%M:%S", &ts);
	return buf;
}

void _util_printf(char *fmt, ...)
{
	// keep it thread-safe
	static __thread char buffer[1024];
	va_list ap;

	snprintf(buffer, sizeof(buffer), "%s%s%s", "[%s ", "thread-%x]\t", fmt);

	va_start(ap, fmt);

	vprintf(buffer, ap);

	va_end(ap);
}

