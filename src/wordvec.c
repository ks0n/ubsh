#define _GNU_SOURCE
#include "wordvec.h"

struct wordvec *wordvec_new(void)
{
	struct wordvec *wv = malloc(sizeof(*wv));
	if (!wv)
		return NULL;

	wv->len = 0;
	wv->cap = WORDVEC_DEFAULT_CAP;

	wv->vec = calloc(wv->cap, sizeof(*wv->vec));
	if (!wv->vec) {
		free(wv);
		return NULL;
	}

	return wv;
}

void wordvec_del(struct wordvec *wv)
{
	free(wv->vec);
	free(wv);
}

static int double_capacity(struct wordvec *wv)
{
	char *new_vec;

	wv->cap *= 2;

	new_vec = reallocarray(wv->vec, wv->cap, sizeof(*wv->vec));
	if (!new_vec)
		return -1;

	wv->vec = new_vec;

	return 0;
}

int wordvec_append(struct wordvec *wv, char c)
{
	if (wv->len >= wv->cap - 1)
		if (double_capacity(wv) < 0)
			return -1;

	wv->vec[wv->len] = c;
	wv->len += 1;

	wv->vec[wv->len] = '\0';

	return 0;
}

int wordvec_pop(struct wordvec *wv)
{
	if (wv->len < 1)
		return 1;

	wv->vec[wv->len - 1] = '\0';
	wv->len -= 1;

	return 0;
}
