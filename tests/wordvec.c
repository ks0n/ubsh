#include <criterion/criterion.h>
#include "wordvec.h"

static struct wordvec *vec;

void setup(void)
{
	vec = wordvec_new();
}

void teardown(void)
{
	wordvec_del(vec);
}

Test(wordvec, valid_empty, .init = setup, .fini = teardown)
{
	cr_assert_eq(vec->len, 0);
	cr_assert_eq(vec->cap, WORDVEC_DEFAULT_CAP);
	cr_assert_str_eq(vec->vec, "");
}

Test(wordvec, valid_small, .init = setup, .fini = teardown)
{
	char *buf = "HEY";
	size_t len = strlen(buf);

	for (size_t i = 0; i < len; i++)
		wordvec_append(vec, buf[i]);

	cr_assert_eq(vec->len, len);
	cr_assert_eq(vec->cap, WORDVEC_DEFAULT_CAP);
	cr_assert_eq(vec->vec[vec->len], '\0');
	cr_assert_str_eq(vec->vec, "HEY");
}

Test(wordvec, valid_realloc, .init = setup, .fini = teardown)
{
	char *buf = "HEY";
	size_t len = strlen(buf);

	for (size_t i = 0; i < WORDVEC_DEFAULT_CAP * 8; i++)
		wordvec_append(vec, buf[i % len]);

	cr_assert_eq(vec->len, WORDVEC_DEFAULT_CAP * 8);
	cr_assert_neq(vec->cap, WORDVEC_DEFAULT_CAP);
	cr_assert_eq(vec->vec[vec->len], '\0');
}
