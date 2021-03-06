#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#include "charstream.h"
#include "token.h"
#include "queue.h"

struct quoting_state {
	bool backslashed;
	bool singlequoted;
	bool doublequoted;
};

struct lexer {
	struct charstream stream;

	struct queue tokens;
};

int lexer_init(struct lexer *l, FILE *input);
void lexer_cleanup(struct lexer *l);

/**
 * Discard the token returned by lexer_peek()
 */
void lexer_consume(struct lexer *l);

/**
 * Return the token that will come out first of the lexer.
 */
inline static struct token *lexer_first(struct lexer *l)
{
	return queue_peek_first(&l->tokens);
}

/**
 * Return the token that will come out last of the lexer.
 * Also the token the lexer is currently editing.
 */
inline static struct token *lexer_last(struct lexer *l)
{
	return queue_peek_last(&l->tokens);
}

const struct token *lexer_peek(struct lexer *l);

#endif /* ! LEXER_H */
