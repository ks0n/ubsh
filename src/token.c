#include "token.h"

#include <stdbool.h>

#include "wordvec.h"
#include "utils.h"

struct token {
  enum toktype type;
  bool quoted;
  bool delimited;


  struct wordvec *word;
};

struct token *token_new(void)
{
	struct token *tok = malloc(sizeof(*tok));
	if (!tok)
		return NULL;

	tok->type = TOKTYPE_UNCATEGORIZED;
	tok->quoted = false;
	tok->delimited = false;

	tok->word = wordvec_new();
	if (!tok->word) {
		free(tok);
		return NULL;
	}

	return tok;
}

void token_del(struct token *tok)
{
	wordvec_del(tok->word);
	free(tok);
}

int token_append(struct token *tok, char c)
{
	if (wordvec_append(tok->word, c) < 0)
		return -1;

	return 0;
}

bool token_is_delimited(const struct token *tok)
{
	return tok->delimited;
}

static bool token_eof_check(struct token *tok) {
	return wordvec_len(tok->word) == 0;
}
static bool token_word_check(struct token *tok) {
	return true;
}

static void categorize(struct token *tok)
{
	struct {
		enum toktype type;
		bool (*check)(struct token *tok);
	} token_check [] = {
		{TOKTYPE_EOF, token_eof_check},
		{TOKTYPE_WORD, token_word_check}
	};
	tok->type = TOKTYPE_UNCATEGORIZED;

	for (size_t i = 0; i < ARRAY_LENGTH(token_check); i++) {
		if ((token_check[i].check)(tok)) {
			tok->type = token_check[i].type;
			return;
		}
	}
}

void token_delimit(struct token *tok)
{
	categorize(tok);

	tok->delimited = true;
}

const char *token_characters(const struct token *tok)
{
	return wordvec_chars(tok->word);
}

enum toktype token_type(const struct token *tok)
{
	return tok->type;
}

bool token_is_eof(const struct token *tok)
{
	return tok->type == TOKTYPE_EOF;
}