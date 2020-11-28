#ifndef NODE_NOT_H
#define NODE_NOT_H

#include "ast/ast.h"

struct node_not {
	AST_NODE_MEMBER;

	struct ast_node *node;
};

const struct ast_node *get_node_not_methods(void);

#endif /* ! NODE_NOT_H */
