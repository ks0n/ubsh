#include "ast/ast.h"
#include "ast/node_list.h"

static struct ast_node *node_list_new(void)
{
	struct node_list *node = malloc(sizeof(*node));

	node->AST_NODE_MEMBER_NAME = *get_node_list_methods();
	node->head = NULL;

	return TO_AST_NODE(node);
}

static void node_list_del(struct ast_node *ast_node)
{
	struct node_list *node = FROM_AST_NODE(ast_node, struct node_list);

	struct linked_list_node *next;
	for (struct linked_list_node *cur = node->head; cur; cur = next) {
		next = cur->next;

		cur->node->del(cur->node);
		free(cur);
	}

	free(node);
}

static int node_list_exec(struct ast_node *ast_node)
{
	int rv = 0;
	struct node_list *node = FROM_AST_NODE(ast_node, struct node_list);

	for (struct linked_list_node *cur = node->head; cur; cur = cur->next)
		rv = cur->node->exec(cur->node);

	return rv;
}

static struct ast_node node_list_methods = {
	.type = "node_list",
	.new = node_list_new,
	.del = node_list_del,
	.exec = node_list_exec,
};

const struct ast_node *get_node_list_methods(void)
{
	return &node_list_methods;
}
