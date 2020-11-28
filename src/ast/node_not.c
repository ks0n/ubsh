#include "ast/node_not.h"
#include "ast/ast.h"

static struct ast_node *node_not_new(void)
{
	struct node_not *node = malloc(sizeof(*node));

	node->AST_NODE_MEMBER_NAME = *get_node_not_methods();
	node->node = NULL;

	return TO_AST_NODE(node);
}

static void node_not_del(struct ast_node *ast_node)
{
	struct node_not *node = FROM_AST_NODE(ast_node, struct node_not);

	node->node->del(node->node);

	free(node);
}

static int node_not_exec(struct ast_node *ast_node)
{
	struct node_not *node = FROM_AST_NODE(ast_node, struct node_not);

	return !node->node->exec(node->node);
}

static struct ast_node node_not_methods = {
	.type = "node_not",
	.new = node_not_new,
	.del = node_not_del,
	.exec = node_not_exec,
};

const struct ast_node *get_node_not_methods(void)
{
	return &node_not_methods;
}
