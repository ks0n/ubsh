#include "lexer.h"

#include <err.h>
#include <ctype.h>
#include <string.h>

#include "logger.h"
#include "utils.h"
#include "wordvec.h"
#include "token_recognition.h"

static void quoting_reset(struct quoting_state *q)
{
	memset(q, 0, sizeof(*q));
}

static bool inside_quoting(const struct quoting_state *q)
{
	return q->backslashed || q->singlequoted || q->doublequoted;
}

int lexer_init(struct lexer *l, FILE *input)
{
	if (charstream_init(&l->stream, input) < 0) {
		LOG(LOG_WARN, "%s: failed to init charstream", __func__);
		return -1;
	}

	queue_init(&l->tokens);

	return 0;
}

static void discard_line(struct lexer *l)
{
	char c;

	do {
		c = charstream_read(&l->stream);
	} while (c != CHARSTREAM_EOF && c != '\n');
}

static void __lexer_delimit(struct lexer *l)
{
	struct token *new;

	token_delimit(lexer_last(l));

	/* TODO: looks like I'm fucked if malloc fails.
	 * (we just need xmalloc)
	 */
	new = token_new();
	queue_push(&l->tokens, new);
}

/**
 * Delimit the latest token the lexer is constructing.
 *
 * If lexer_consume is called again, it will start work on a new token.
 */
static void lexer_delimit(struct lexer *l)
{
	/* Don't create empty tokens. EOF is an exception.
	 * https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03
	 * 'If it is indicated that a token is delimited, and no characters
	 *  have been included in a token, processing shall continue until an
	 *  actual token is delimited.'
	 */
	if (token_length(lexer_last(l)) == 0)
		return;

	__lexer_delimit(l);
}

static void lexer_delimit_eof(struct lexer *l)
{
	__lexer_delimit(l);
}

/**
 * Append a character to the latest token the lexer is constructing.
 */
static int lexer_append_char(struct lexer *l, char c)
{
	struct token *cur = lexer_last(l);

	return token_append(cur, c);
}

/**
 * Wether the lexer has a delimited token.
 */
static bool lexer_has_delimited(struct lexer *l)
{
	struct token *cur = lexer_first(l);

	if (!cur)
		return false;

	return token_is_delimited(cur);
}

static int handle_quoted(struct lexer *l, struct quoting_state *quoting, char c)
{
	if (quoting->singlequoted && c == '\'') {
		quoting->singlequoted = false;
		return 0;
	}

	if (quoting->doublequoted && c == '"') {
		quoting->doublequoted = false;
		return 0;
	}

	if (lexer_append_char(l, c) < 0)
		return -1;

	return 0;
}

static int handle_unquoted(struct lexer *l, struct quoting_state *quoting,
			   char c)
{
	/* Returning 0 means you have finished processing the current char. */

	if (token_is_operator(lexer_last(l))) {
		enum toktype possible_type = TOKTYPE_UNCATEGORIZED;
		if (can_form_operator(lexer_last(l), c, &possible_type)) {
			lexer_append_char(l, c);
			lexer_last(l)->type = possible_type;

			return 0;
		}
		lexer_delimit(l);

		/* Fallthrough to last case lexer_append_char. */
	}

	if (can_start_operator(c)) {
		lexer_delimit(l);

		lexer_last(l)->type = TOKTYPE_OPERATOR;
		/* Fallthrough to last case lexer_append_char. */
	}

	if (c == '\\') {
		quoting->backslashed = true;
		return 0;
	}

	if (c == '\'') {
		quoting->singlequoted = true;
		return 0;
	}

	if (c == '"') {
		quoting->doublequoted = true;
		return 0;
	}

	if (c == '#') {
		discard_line(l);
		return 0;
	}

	if (isblank(c)) {
		lexer_delimit(l);
		return 0;
	}

	if (c == '\n') {
		lexer_delimit(l);
		return 0;
	}

	if (lexer_append_char(l, c) < 0)
		return -1;

	return 0;
}

static int lexer_consume_char(struct lexer *l, struct quoting_state *quoting)
{
	char c = charstream_read(&l->stream);
	bool is_quoted;

	/*
	 * Save if we are currently quoted.
	 * If it was backslash quoting disable so that the future chars aren't backslash quoted too.
	 * Since be saved the if we were quoted, the current char will be fine quote-wise
         */
	is_quoted = inside_quoting(quoting);
	if (quoting->backslashed)
		quoting->backslashed = false;

	if (c == CHARSTREAM_EOF) {
		lexer_delimit_eof(l);
		return 0;
	}

	if (is_quoted)
		handle_quoted(l, quoting, c);
	else
		handle_unquoted(l, quoting, c);

	return 0;
}

static void pop_lexer_first_if_delimited(struct lexer *l)
{
	struct token *tok;

	if (!queue_is_empty(&l->tokens) && token_is_delimited(lexer_first(l))) {
		tok = queue_pop(&l->tokens);
		token_del(tok);
	}
}

static void add_token_if_none_present(struct lexer *l)
{
	if (queue_is_empty(&l->tokens)) {
		struct token *tok = token_new();
		queue_push(&l->tokens, tok);
	}
}

static void setup_lexer(struct lexer *l)
{
	pop_lexer_first_if_delimited(l);
	add_token_if_none_present(l);
}

const struct token *lexer_consume(struct lexer *l)
{
	struct quoting_state quoting;
	quoting_reset(&quoting);

	setup_lexer(l);

	while (!lexer_has_delimited(l)) {
		lexer_consume_char(l, &quoting);
	}

	return lexer_first(l);
}

/**
 * Free data owned by the lexer @l
 */
void lexer_cleanup(struct lexer *l)
{
	struct token *tok;
	while (!queue_is_empty(&l->tokens)) {
		tok = queue_pop(&l->tokens);

		token_del(tok);
	}
}
