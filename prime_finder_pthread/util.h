#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdarg.h>
#include <stdlib.h>

#include <inttypes.h>
#define __STDC_FORMAT_MACROS

/*
 * Return a string stored in 'static area' to specify the current time
 */
extern char* get_time();

typedef enum {INFO, WARNING, ERROR} log_level;

#define util_printf(format, args...)\
	_util_printf((char*)(format), get_time(), pthread_self(), args);

/*Do NOT directly call this!*/
extern void _util_printf(char *fmt, ...);

#endif

