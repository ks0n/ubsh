#ifndef NODE_SIMPLE_COMMAND
#define NODE_SIMPLE_COMMAND

#include "ast/ast.h"

struct node_simple_command {
	AST_NODE_MEMBER;

	char *command;
};

const struct ast_node *get_node_simple_command_methods(void);

#endif /* ! NODE_SIMPLE_COMMAND */
