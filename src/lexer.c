#include "lexer.h"

#include <err.h>
#include <ctype.h>
#include <string.h>

static void quoting_reset(struct quoting_state *q)
{
	memset(q, 0, sizeof(*q));
}

static bool inside_quoting(const struct quoting_state *q)
{
	return q->backslashed == true;
}

int lexer_init(struct lexer *l, FILE *input)
{
	if (charstream_init(&l->stream, input) < 0) {
		warnx("%s: failed to init charstream", __FUNCTION__);
		return -1;
	}

	quoting_reset(&l->quoting);

	l->cur = NULL;

	return 0;
}

static void discard_line(struct lexer *l)
{
	char c;

	do {
		c = charstream_read(&l->stream);
	} while (c != CHARSTREAM_EOF && c != '\n');
}

static int lexer_consume_char(struct lexer *l, struct token *tok)
{
	char c = charstream_read(&l->stream);
	bool is_quoted = inside_quoting(&l->quoting);

	/* step_quoting */
	if (l->quoting.backslashed > 0)
		l->quoting.backslashed--;

	if (c == CHARSTREAM_EOF) {
		token_delimit(tok);
		return 0;
	}

	if (!is_quoted && c == '\\') {
		l->quoting.backslashed = 1;
		return 0;
	}

	if (!is_quoted && c == '#') {
		discard_line(l);
		return 0;
	}

	if (!is_quoted && isblank(c)) {
		token_delimit(tok);
		return 0;
	}

	if (!is_quoted && c == '\n') {
		token_delimit(tok);
		return 0;
	}

	if (token_append(tok, c) < 0)
		return -1;

	return 0;
}

/**
 * Read chars from the charstream owned by @l until a token is delimited.
 * Think of this as an iterator over the input tokens.
 *
 * @return token read by the lexer (the token is owned by the lexer)
 */
const struct token *lexer_read(struct lexer *l)
{
	if (l->cur)
		token_del(l->cur);

	l->cur = token_new();
	if (!l->cur) {
		warnx("%s: failed to create token", __FUNCTION__);
		return NULL;
	}

	while (!token_is_delimited(l->cur)) {
		lexer_consume_char(l, l->cur);
	}

	return l->cur;
}

/**
 * Free data owned by the lexer @l
 */
void lexer_cleanup(struct lexer *l)
{
	if (l->cur)
		token_del(l->cur);
}
