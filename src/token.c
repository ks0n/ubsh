#include "token.h"

#include <stdbool.h>
#include <string.h>

#include "wordvec.h"
#include "utils.h"

struct token *token_new(void)
{
	struct token *tok = calloc(1, sizeof(*tok));
	if (!tok)
		return NULL;

	tok->type = TOKTYPE_UNCATEGORIZED;
	tok->quoted = false;
	tok->delimited = false;

	tok->word = wordvec_new();
	tok->quote_map = wordvec_new();
	if (!tok->word || !tok->quote_map) {
		free(tok->word);
		free(tok->quote_map);
		free(tok);
		return NULL;
	}

	return tok;
}

void token_del(struct token *tok)
{
	wordvec_del(tok->word);
	wordvec_del(tok->quote_map);
	free(tok);
}

int token_append(struct token *tok, char c, bool quoted)
{
	if (wordvec_append(tok->word, c) < 0)
		return -1;

	if (wordvec_append(tok->quote_map, quoted) < 0)
		return -1;

	return 0;
}

int token_pop(struct token *tok)
{
	wordvec_pop(tok->quote_map);
	return wordvec_pop(tok->word);
}

bool token_is_delimited(const struct token *tok)
{
	return tok->delimited;
}

static bool token_eof_check(struct token *tok)
{
	return wordvec_len(tok->word) == 0;
}

static bool token_word_check(struct token *tok)
{
	return true;
}

static bool token_not_check(struct token *tok)
{
	return !token_strcmp(tok, "!") && !token_is_quoted_at(tok, 0);
}

static void categorize(struct token *tok)
{
	struct {
		enum toktype type;
		bool (*check)(struct token *tok);
	} token_check[] = { { TOKTYPE_EOF, token_eof_check },
			    { TOKTYPE_NOT, token_not_check },
			    { TOKTYPE_WORD, token_word_check } };

	/* We might already have an obvious categorization at this stage */
	if (tok->type != TOKTYPE_UNCATEGORIZED)
		return;

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

int token_strcmp(const struct token *tok, const char *str)
{
	return strcmp(token_characters(tok), str);
}

enum toktype token_type(const struct token *tok)
{
	return tok->type;
}

int token_is_quoted_at(const struct token *tok, size_t index)
{
	return wordvec_get(tok->quote_map, index);
}

bool token_is_eof(const struct token *tok)
{
	return tok->type == TOKTYPE_EOF;
}

bool token_is_operator(const struct token *tok)
{
	switch (tok->type) {
	case TOKTYPE_OPERATOR:
	case TOKTYPE_AND_IF:
	case TOKTYPE_OR_IF:
	case TOKTYPE_DSEMI:
	case TOKTYPE_DLESS:
	case TOKTYPE_DGREAT:
	case TOKTYPE_LESSAND:
	case TOKTYPE_GREATAND:
	case TOKTYPE_LESSGREAT:
	case TOKTYPE_DLESSDASH:
	case TOKTYPE_CLOBBER:
		return true;
	default:
		return false;
	}
}

bool token_is_separator_op(const struct token *tok)
{
	/* Checks according to:
	 * https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02
	 */
	// TODO: check if token is quoted.

	return token_type(tok) == TOKTYPE_SEP_SEMI ||
	       token_type(tok) == TOKTYPE_SEP_AND;
}

size_t token_length(const struct token *tok)
{
	return wordvec_len(tok->word);
}
