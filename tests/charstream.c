#include <criterion/criterion.h>

#include "charstream.h"

#define STRING_TEST "test"

static FILE *open_string(char *str)
{
	return fmemopen(str, strlen(str), "r");
}

Test(charstream, charstream_init)
{
	struct charstream charstream;
	FILE *file = open_string(STRING_TEST);
	int res = charstream_init(&charstream, file);

	cr_assert_eq(res, 0);
}

Test(charstream, charstream_read)
{
	char *str = STRING_TEST;
	struct charstream charstream;
	FILE *file = open_string(str);
	charstream_init(&charstream, file);

	char c;
	for (size_t i = 0; i < strlen(str); i++) {
		c = charstream_read(&charstream);
		cr_assert_eq(c, str[i]);
	}

	c = charstream_read(&charstream);
	cr_assert_eq(c, CHARSTREAM_EOF);
}

Test(charstream, charstream_peek)
{
	char *str = STRING_TEST;
	struct charstream charstream;
	FILE *file = open_string(str);
	charstream_init(&charstream, file);

	char c1 = charstream_peek(&charstream);
	char c2 = charstream_peek(&charstream);

	cr_assert_eq(c1, str[0]);
	cr_assert_eq(c2, str[0]);
}
