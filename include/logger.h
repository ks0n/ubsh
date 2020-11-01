#ifndef LOGGER_H
#define LOGGER_H

#include <err.h>
#include <stdio.h>

#include "color.h"

/* Error code to use when logging a fatal error */
#define LOG_EXIT_CODE 3

/**
 * Logging levels available
 */
enum log_level {
	LOG_INFO = 0,
	LOG_WARN,
	LOG_ERR,
	LOG_FATAL_ERR,
};

#define __INNER_PRINT_ARGS(...)                                                \
	do {                                                                   \
		fprintf(stderr, __VA_ARGS__);                                  \
		fprintf(stderr, "\n");                                         \
	} while (0)

/* Logging doesn't need to show on release builds */
#ifdef NDEBUG
/**
 * Only log errors and fatal errors in release mode
 */
#define LOG(__LEVEL, ...)                                                      \
	do {                                                                   \
		if (__LEVEL >= LOG_ERR)                                        \
			if (print_level(__LEVEL) == 0)                         \
				__INNER_PRINT_ARGS(__VA_ARGS__);               \
	} while (0)
#else
/**
 * Simple Logging macro. Pass a level and a formatting string
 *
 * @param __LEVEL Logging level to use, from the @log_level enum
 * @param ... Formatting string as you would give to a printf-like function.
 *
 * ```c
 * LOG(LOG_ERR, "%d does not equal %d!", 3, 2);
 * LOG(LOG_INFO, "Job number %d has been interrupted", job_nb);
 * LOG(LOG_WARN, "This is a warning");
 * ```
 */
#define LOG(__LEVEL, ...)                                                      \
	do {                                                                   \
		if (print_level(__LEVEL) == 0)                                 \
			__INNER_PRINT_ARGS(__VA_ARGS__);                       \
		if (__LEVEL == LOG_FATAL_ERR)                                  \
			errx(LOG_EXIT_CODE, NULL);                             \
	} while (0)
#endif

/**
 * Prints the level of logging according to its value.
 *
 * @warning Do not use directly, use the LOG() macro
 */
static inline int print_level(enum log_level level)
{
	switch (level) {
	case LOG_INFO:
		fprintf(stderr, BLUE("INFO") ": ");
		return 0;
	case LOG_WARN:
		fprintf(stderr, YELLOW("WARN") ": ");
		return 0;
	case LOG_ERR:
		fprintf(stderr, RED("ERROR") ": ");
		return 0;
	case LOG_FATAL_ERR:
		fprintf(stderr, RED_HI("FATAL ERROR") ": ");
		return 0;
	default:
		LOG(LOG_ERR, "UNKNOWN LOG LEVEL");
		return -1;
	}
}

#endif /* ! LOGGER_H */
