#include <assert.h>

#include "charstream.h"
#include "utils.h"

static char get_error(struct charstream *cs)
{
	char chr;
	if (feof(cs->file)) {
		chr = CHARSTREAM_EOF;
	} else {
		chr = CHARSTREAM_ERR;
	}
	clearerr(cs->file);

	return chr;
}

int charstream_init(struct charstream *cs, FILE *file)
{
	assert(file);

	cs->file = file;

	return 0;
}
char charstream_read(struct charstream *cs)
{
	char chr = fgetc(cs->file);
	if (chr == EOF) {
		return get_error(cs);
	}

	return chr;
}

char charstream_peek(struct charstream *cs)
{
	char chr = charstream_read(cs);
	if (chr != CHARSTREAM_ERR && chr != CHARSTREAM_EOF)
		if (ungetc(chr, cs->file) == EOF)
			return get_error(cs);

	return chr;
}
