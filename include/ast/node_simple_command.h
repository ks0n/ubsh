#ifndef NODE_SIMPLE_COMMAND_H
#define NODE_SIMPLE_COMMAND_H

#include "ast/ast.h"

// TODO: This need to be changed (ex: Lots of files when creating a tarball)
#define ARGV_MAX 512

struct node_simple_command {
	AST_NODE_MEMBER;

	int argc;
	char *argv[ARGV_MAX];
};

const struct ast_node *get_node_simple_command_methods(void);

#endif /* ! NODE_SIMPLE_COMMAND_H */
