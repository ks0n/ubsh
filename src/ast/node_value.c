#include <stdlib.h>

#include "ast.h"
#include "node_value.h"

#include "utils.h"

static struct ast_node *node_value_new(void)
{
	struct node_value *node = malloc(sizeof(*node));
	if (!node)
		return NULL;

	node->AST_NODE_MEMBER_NAME = *get_node_value_base();
	node->value = NULL;

	return TO_AST_NODE(node);
}

static void node_value_del(struct ast_node *ast_node)
{
	struct node_value *node = FROM_AST_NODE(ast_node, struct node_value);

	free(node->value);
	free(node);
}

static int node_value_exec(struct ast_node *ast_node)
{
	struct node_value *node = FROM_AST_NODE(ast_node, struct node_value);

	if (!node->value)
		return AST_ERR;

	return AST_OK;
}

static struct ast_node node_value_base = {
	.type = "node_value",
	.new = node_value_new,
	.del = node_value_del,
	.exec = node_value_exec,
};

const struct ast_node *get_node_value_base(void)
{
	return &node_value_base;
}
