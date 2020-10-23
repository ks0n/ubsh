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

Test(lexer, doublequoted_three_words)
{
	struct lexer l = open_lexer("\"one two three\"");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "one two three");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, singlequotes_inside_doublequotes)
{
	struct lexer l = open_lexer("\"'one two three'\"");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "'one two three'");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, half_commented_line)
{
	struct lexer l = open_lexer("i am #a line");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "i");

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "am");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, backquoted_comment)
{
	struct lexer l = open_lexer("i am \\#a line");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "i");

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "am");

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "#a");

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "line");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, doublequoted_comment)
{
	struct lexer l = open_lexer("\"i am #a line\"");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "i am #a line");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, backquoted_comment_inside_doublequotes)
{
	struct lexer l = open_lexer("\"i am \\#a line\"");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "i am \\#a line");

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

Test(lexer, op_or_if)
{
	struct lexer l = open_lexer("a || b");
	const struct token *tok;

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "a");
	cr_assert_eq(token_type(tok), TOKTYPE_WORD);

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "||");
	cr_assert_eq(token_type(tok), TOKTYPE_OR_IF);

	tok = lexer_consume(&l);
	cr_assert_str_eq(token_characters(tok), "b");
	cr_assert_eq(token_type(tok), TOKTYPE_WORD);

	tok = lexer_consume(&l);
	cr_assert(token_is_eof(tok));

	close_lexer(&l);
}

/* #<{(| Test(lexer, unfinished_dless) |)}># */
/* int main() */
/* { */
/* 	struct lexer l = open_lexer("ta<mer"); */
/* 	const struct token *tok; */
/*  */
/* 	tok = lexer_consume(&l); */
/* 	cr_assert_str_eq(token_characters(tok), "ta"); */
/* 	cr_assert_eq(token_type(tok), TOKTYPE_WORD); */
/*  */
/* 	tok = lexer_consume(&l); */
/* 	cr_assert_str_eq(token_characters(tok), "<"); */
/* 	cr_assert_eq(token_type(tok), TOKTYPE_OPERATOR); */
/*  */
/* 	tok = lexer_consume(&l); */
/* 	cr_assert_str_eq(token_characters(tok), "mer"); */
/* 	cr_assert_eq(token_type(tok), TOKTYPE_WORD); */
/*  */
/* 	tok = lexer_consume(&l); */
/* 	cr_assert(token_is_eof(tok)); */
/*  */
/* 	close_lexer(&l); */
/* } */
