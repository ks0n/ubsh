#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdbool.h>

enum toktype {
	TOKTYPE_UNCATEGORIZED,
	TOKTYPE_WORD,
	TOKTYPE_EOF,

	/* Operators */
	TOKTYPE_OPERATOR, /* Place holder when we don't know yet */
	TOKTYPE_AND_IF, /* && */
	TOKTYPE_OR_IF, /* || */
	TOKTYPE_DSEMI, /* ;; */
	TOKTYPE_DLESS, /* << */
	TOKTYPE_DGREAT, /* >> */
	TOKTYPE_LESSAND, /* <& */
	TOKTYPE_GREATAND, /* >& */
	TOKTYPE_LESSGREAT, /* <> */
	TOKTYPE_DLESSDASH, /* <<- */
	TOKTYPE_CLOBBER, /* >| */

	/* Custom operators defined by ubsh */
	TOKTYPE_SEP_SEMI,
	TOKTYPE_SEP_AND,
	TOKTYPE_NOT,
};

struct token {
	enum toktype type;
	bool quoted;
	bool delimited;

	struct wordvec *word;
	struct wordvec *quote_map;
};

struct token *token_new(void);
void token_del(struct token *tok);

int token_append(struct token *tok, char c, bool quoted);
int token_pop(struct token *tok);

bool token_is_delimited(const struct token *tok);
void token_delimit(struct token *tok);

const char *token_characters(const struct token *tok);
int token_strcmp(const struct token *tok, const char *str);

enum toktype token_type(const struct token *tok);

int token_is_quoted_at(const struct token *tok, size_t index);

bool token_is_eof(const struct token *tok);
bool token_is_operator(const struct token *tok);

bool token_is_separator_op(const struct token *tok);

size_t token_length(const struct token *tok);

#endif /* ! TOKEN_H */
