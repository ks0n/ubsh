#ifndef UTILS_H
#define UTILS_H

#include <err.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Mark a function as unimplemented and error out when called
 */
#define UNIMPLEMENTED()                                                        \
	errx(EXIT_FAILURE, "function %s in %s:%d not implemented", __func__,   \
	     __FILE__, __LINE__)

/**
 * Mark argument as `unused`, for example when developing unimplemented functions
 */
#define UNUSED(__ARG) __attribute__((__unused__)) __ARG

/**
 * Create a unique phantom member to a struct to avoid empty structs.
 *
 * @warn Using PHANTOM in release mode is forbidden!
 */
#ifndef NDEBUG
#define PHANTOM uint8_t __phantom_data
#else
#define PHANTOM invalid_phantom_type phantom_data
#endif /* ! NDEBUG */

#endif /* ! UTILS_H */
