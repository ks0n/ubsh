#include "token_recognition.h"

#include <string.h>

#include "utils.h"
#include "wordvec.h"

struct {
	const char *str;
	enum toktype type;
} operators[] = {
	{ "&&", TOKTYPE_AND_IF },     { "||", TOKTYPE_OR_IF },
	{ ";;", TOKTYPE_DSEMI },      { "<<", TOKTYPE_DLESS },
	{ ">>", TOKTYPE_DGREAT },     { "<&", TOKTYPE_LESSAND },
	{ ">&", TOKTYPE_GREATAND },   { "<>", TOKTYPE_LESSGREAT },
	{ "<<-", TOKTYPE_DLESSDASH }, { ">|", TOKTYPE_CLOBBER },
};

bool can_start_operator(char c)
{
	for (size_t i = 0; i < ARRAY_LENGTH(operators); i++) {
		if (operators[i].str[0] == c)
			return true;
	}

	return false;
}

bool can_form_operator(struct token *tok, char c, enum toktype *type)
{
	size_t i;
	bool found = false;
	size_t tok_len = wordvec_len(tok->word);

	if (tok_len < 1)
		return found;

	token_append(tok, c);
	tok_len = wordvec_len(tok->word);

	for (i = 0; i < ARRAY_LENGTH(operators); i++) {
		if (!strncmp(token_characters(tok), operators[i].str,
			     tok_len)) {
			found = true;
			break;
		}
	}

	if (found && type != NULL)
		*type = operators[i].type;

	token_pop(tok);
	return found;
}
