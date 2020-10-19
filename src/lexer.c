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

/**
 * Delimit the latest token the lexer is constructing.
 *
 * If lexer_consume is called again, it will start work on a new token.
 */
static void lexer_delimit(struct lexer *l)
{
	token_delimit(l->cur);
}

/**
 * Append a character to the latest token the lexer is constructing.
 */
static int lexer_append_char(struct lexer *l, char c)
{
	return token_append(l->cur, c);
}

/**
 * Wether the lexer has delimited its latest token.
 */
static bool lexer_has_delimited(struct lexer *l)
{
	return token_is_delimited(l->cur);
}

static int lexer_consume_char(struct lexer *l)
{
	char c = charstream_read(&l->stream);
	bool is_quoted = inside_quoting(&l->quoting);

	/* step_quoting */
	if (l->quoting.backslashed)
		l->quoting.backslashed = false;

	if (c == CHARSTREAM_EOF) {
		lexer_delimit(l);
		return 0;
	}

	if (!is_quoted && c == '\\') {
		l->quoting.backslashed = true;
		return 0;
	}

	if (!is_quoted && c == '#') {
		discard_line(l);
		return 0;
	}

	if (!is_quoted && isblank(c)) {
		lexer_delimit(l);
		return 0;
	}

	if (!is_quoted && c == '\n') {
		lexer_delimit(l);
		return 0;
	}

	if (lexer_append_char(l, c) < 0)
		return -1;

	return 0;
}

const struct token *lexer_consume(struct lexer *l)
{
	struct quoting_state quoting;
	quoting_reset(&quoting);

	if (l->cur)
		token_del(l->cur);

	l->cur = token_new();
	if (!l->cur) {
		warnx("%s: failed to create token", __FUNCTION__);
		return NULL;
	}

	while (!lexer_has_delimited(l)) {
		lexer_consume_char(l);
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
