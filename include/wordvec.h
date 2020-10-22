#ifndef WORDVEC_H
#define WORDVEC_H

#include <stdlib.h>

#define WORDVEC_DEFAULT_CAP 8

struct wordvec {
	size_t cap;
	size_t len;
	char *vec;
};

struct wordvec *wordvec_new(void);
void wordvec_del(struct wordvec *wv);

int wordvec_append(struct wordvec *wv, char c);
int wordvec_pop(struct wordvec *wv);

static inline const char *wordvec_chars(const struct wordvec *wv)
{
	return wv->vec;
}

static inline size_t wordvec_len(const struct wordvec *wv)
{
	return wv->len;
}

#endif /* ! WORDVEC_H */
