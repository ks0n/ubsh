#ifndef NODE_SIMPLE_COMMAND
#define NODE_SIMPLE_COMMAND

#include "ast/ast.h"

#define ARGV_MAX 512

struct node_simple_command {
	AST_NODE_MEMBER;

  int argc;
	char *argv[ARGV_MAX];
};

const struct ast_node *get_node_simple_command_methods(void);

#endif /* ! NODE_SIMPLE_COMMAND */
