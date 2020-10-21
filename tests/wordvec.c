#include <criterion/criterion.h>
#include "wordvec.h"

Test(wordvec, valid_empty)
{
    struct wordvec *vec = wordvec_new();

    cr_assert_eq(vec->len, 0);
    cr_assert_eq(vec->cap, WORDVEC_DEFAULT_CAP);
    cr_assert_str_eq(vec->vec, "");

    wordvec_del(vec);
}

Test(wordvec, valid_small)
{
    struct wordvec *vec = wordvec_new();

    char *buf = "HEY";
    size_t len = strlen(buf);

    for (size_t i = 0; i < len; i++)
        wordvec_append(vec, buf[i]);

    cr_assert_eq(vec->len, len);
    cr_assert_eq(vec->cap, WORDVEC_DEFAULT_CAP);
    cr_assert_eq(vec->vec[vec->len], '\0');
    cr_assert_str_eq(vec->vec, "HEY");

    wordvec_del(vec);
}

Test(wordvec, valid_realloc)
{
    struct wordvec *vec = wordvec_new();

    char *buf = "HEY";
    size_t len = strlen(buf);

    for (size_t i = 0; i < WORDVEC_DEFAULT_CAP * 8; i++)
        wordvec_append(vec, buf[i % len]);

    cr_assert_eq(vec->len, WORDVEC_DEFAULT_CAP * 8);
    cr_assert_neq(vec->cap, WORDVEC_DEFAULT_CAP);
    cr_assert_eq(vec->vec[vec->len], '\0');

    wordvec_del(vec);
}
