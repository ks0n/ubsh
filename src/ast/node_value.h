#include "ast.h"

struct node_value {
	AST_NODE_MEMBER;

	char *value;
};

const struct ast_node *get_node_value_base(void);
