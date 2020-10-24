#include "ast.h"
#include "ast_value.h"

#include <stdlib.h>

static ast_node_new_f constructors[AST_TYPE_LEN] = {
	[AST_NONE] = NULL,
	[AST_VALUE] = ast_value_new,
};

static ast_node_del_f destructors[AST_TYPE_LEN] = {
	[AST_NONE] = NULL,
	[AST_VALUE] = ast_value_del,
};

static ast_node_exec_f executors[AST_TYPE_LEN] = {
	[AST_NONE] = NULL,
    [AST_VALUE] = ast_value_exec,
};

struct ast_node *ast_node_new(enum ast_type type)
{
	if (type >= AST_TYPE_LEN || !constructors[type])
		return NULL;

	struct ast_node *generic_node = constructors[type]();
	generic_node->type = type;

	return generic_node;
}

int ast_node_del(struct ast_node *node, enum ast_type type)
{
	if (type >= AST_TYPE_LEN)
		return AST_INVALID_LEN;

	if (!destructors[type])
		return AST_UNIMPLEMENTED;

	if (!node)
		return AST_NULL_PTR;

	if (type != node->type)
		return AST_INVALID_TYPE;

	destructors[type](node);

	return AST_OK;
}

int ast_node_exec(struct ast_node *node, enum ast_type type)
{
	if (type >= AST_TYPE_LEN)
		return AST_INVALID_LEN;

	if (!destructors[type])
		return AST_UNIMPLEMENTED;

	if (!node)
		return AST_NULL_PTR;

	if (type != node->type)
		return AST_INVALID_TYPE;

    return executors[type](node);
}
