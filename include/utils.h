#ifndef UTILS_H
#define UTILS_H

#include <err.h>
#include <stdlib.h>

#define UNIMPLEMENTED()                                                        \
	errx(EXIT_FAILURE, "function %s in %s:%d not implemented", __func__,   \
	     __FILE__, __LINE__)

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(*(array)))

#define UNUSED __attribute__((unused))

#endif /* ! UTILS_H */
