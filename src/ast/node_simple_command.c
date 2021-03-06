#include "ast/node_simple_command.h"

#include <stdlib.h>

#include "command.h"

struct ast_node *node_simple_command_new(void)
{
	struct node_simple_command *node = malloc(sizeof(*node));
	if (!node)
		return NULL;

	node->AST_NODE_MEMBER_NAME = *get_node_simple_command_methods();
	node->argc = 0;
	node->argv[0] = NULL;

	return TO_AST_NODE(node);
}

void node_simple_command_del(struct ast_node *ast_node)
{
	struct node_simple_command *node =
		FROM_AST_NODE(ast_node, struct node_simple_command);

	for (int i = 0; i < node->argc; i++)
		free(node->argv[i]);

	free(node);
}

int node_simple_command_exec(struct ast_node *ast_node)
{
	struct node_simple_command *node =
		FROM_AST_NODE(ast_node, struct node_simple_command);

	return command_execute(node->argc, node->argv);
}

static struct ast_node node_simple_command = {
	.type = "node_simple_command",
	.new = node_simple_command_new,
	.del = node_simple_command_del,
	.exec = node_simple_command_exec,
};

const struct ast_node *get_node_simple_command_methods(void)
{
	return &node_simple_command;
}
