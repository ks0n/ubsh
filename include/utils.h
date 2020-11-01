#ifndef UTILS_H
#define UTILS_H

#include <err.h>
#include <stdlib.h>
#include <stddef.h>

#define UNIMPLEMENTED()                                                        \
	errx(EXIT_FAILURE, "function %s in %s:%d not implemented", __func__,   \
	     __FILE__, __LINE__)

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(*(array)))

#define UNUSED __attribute__((unused))

#define container_of(ptr, type, member) ({                      \
	const __typeof__( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type,member) );})

#endif /* ! UTILS_H */
