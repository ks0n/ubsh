#ifndef NODE_VALUE_H
#define NODE_VALUE_H

#include "ast.h"

struct node_value {
	AST_NODE_MEMBER;

	char *value;
};

const struct ast_node *get_node_value_methods(void);

#endif /* ! NODE_VALUE_H */
