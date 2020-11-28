#ifndef NODE_LIST
#define NODE_LIST

#include "ast/ast.h"

struct linked_list_node {
	struct ast_node *node;
	struct linked_list_node *next;
};

struct node_list {
	AST_NODE_MEMBER;

	struct linked_list_node *head;
};

const struct ast_node *get_node_list_methods(void);

#endif /* ! NODE_LIST */
