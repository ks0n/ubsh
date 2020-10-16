#ifndef CHARSTREAM_H
#define CHARSTREAM_H

#include <stdio.h>

/**
 * @file charstream.h
 * Transform input from a file descriptor into a stream of characters.
 */

struct charstream {
	/* Empty for now, it will be filled as implementation is written. */
};

int charstream_init(struct charstream *cs, FILE *file);
char charstream_read(struct charstream *cs);
char charstream_peek(struct charstream *cs);

#endif /* ! CHARSTREAM_H */
