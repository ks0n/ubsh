#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#include "charstream.h"
#include "token.h"

struct quoting_state {
	bool backslashed;
};

struct lexer {
	struct charstream stream;
	struct quoting_state quoting;

	struct token *cur;
};

int lexer_init(struct lexer *l, FILE *input);
void lexer_cleanup(struct lexer *l);

const struct token *lexer_consume(struct lexer *l);

#endif /* ! LEXER_H */
