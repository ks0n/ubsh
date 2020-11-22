#include "ast/parser.h"

#include <string.h>

#include "ast/node_list.h"
#include "ast/node_simple_command.h"

static int parse_simple_command(struct ast_node **simple_command, struct lexer *l)
{
	*simple_command = get_node_simple_command_methods()->new();
	struct node_simple_command *node = FROM_AST_NODE(*simple_command, struct node_simple_command);

	// TODO: parse multiple word commands.
	// for this to work, we need to better and lexer categorized (make sure only words show up as words)

	const struct token *tok = lexer_consume(l);

	node->command = strdup(token_characters(tok));

	return 0;
}

static int parse_list(struct ast_node **root, struct lexer *l)
{
	const struct token *tok;
	*root = get_node_list_methods()->new();
	struct node_list *list = FROM_AST_NODE(*root, struct node_list);

	struct linked_list_node **cur_and_or = &list->head;

	while (1) {
		*cur_and_or = calloc(1, sizeof(**cur_and_or));

		// TODO: parse and_or, ..., command
		parse_simple_command(&((*cur_and_or)->node), l);

		cur_and_or = &((*cur_and_or)->next);

		tok = lexer_peek(l);

		// TODO: we need to be able to check if this is TOKTYPE_WORD
		if (!token_is_separator_op(tok))
			break;
		
		lexer_consume(l);
	}

	return 0;
}

int parser_parse(struct ast_node **root, struct lexer *l)
{
	const struct token *tok;

	*root = NULL;

	tok = lexer_peek(l);
	if (token_is_eof(tok))
		return 0;

	return parse_list(root, l);
}
