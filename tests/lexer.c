#include <criterion/criterion.h>

#include "lexer.h"

static struct lexer open_lexer(char *s)
{
	struct lexer lexer;
	FILE *file = fmemopen(s, strlen(s), "r");

	lexer_init(&lexer, file);

	return lexer;
}

static void close_lexer(struct lexer *l)
{
	lexer_cleanup(l);
	fclose(l->stream.file);
}

Test(lexer, just_spaces)
{
	struct lexer l = open_lexer("    ");
	const struct token *tok = lexer_consume(&l);

	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, one_word)
{
	struct lexer l = open_lexer("iamawork");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "iamawork");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, three_words_with_whitespace)
{
	struct lexer l = open_lexer(" one   two three  ");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "one");

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "two");

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "three");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, singlequoted_three_words)
{
	struct lexer l = open_lexer("'one two three'");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "one two three");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, backquoted_singlequote)
{
	struct lexer l = open_lexer("o\\'ne");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "o'ne");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, backquoted_backquote)
{
	struct lexer l = open_lexer("o\\\\ne");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "o\\ne");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}
