#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <stdbool.h>

struct token;

enum toktype {
  TOKTYPE_UNCATEGORIZED,
  TOKTYPE_WORD,
  TOKTYPE_OPERATOR,
  TOKTYPE_EOF,
};

struct token *token_new(void);
void token_del(struct token *tok);

int token_append(struct token *tok, char c);

bool token_finished(const struct token *tok);
void token_finish(struct token *tok);

const char *token_characters(const struct token *tok);

enum toktype token_type(const struct token *tok);

bool token_is_eof(const struct token *tok);


#endif /* ! TOKEN_H */
