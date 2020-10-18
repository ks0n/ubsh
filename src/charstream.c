#include <assert.h>

#include "charstream.h"
#include "utils.h"

int charstream_init(struct charstream *cs, FILE *file)
{
	assert(file);

	cs->file = file;

	return 0;
}
char charstream_read(struct charstream *cs)
{
	char chr;
	if (fread(&chr, sizeof(char), 1, cs->file) == 0) {
		if (feof(cs->file)) {
			chr = CHARSTREAM_EOF;
		} else {
			chr = CHARSTREAM_ERR;
		}
		clearerr(cs->file);
	}

	return chr;
}

char charstream_peek(struct charstream *cs)
{
	char chr = charstream_read(cs);
	if (chr != CHARSTREAM_ERR)
		fseek(cs->file, -1, SEEK_CUR);

	return chr;
}
