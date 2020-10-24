#include <stdlib.h>

#include "ast_value.h"

#include "utils.h"

AST_CONSTRUCTOR(ast_value_new)
{
	struct ast_value *node = malloc(sizeof(struct ast_value));

	node->value = NULL;

	return UPCAST(node);
}

AST_DESTRUCTOR(ast_value_del, void_node)
{
	struct ast_value *node = (struct ast_value *)void_node;

	free(node->value);
	free(node);
}

AST_EXECUTOR(ast_value_exec, void_node)
{
	struct ast_value *node = (struct ast_value *)void_node;

	if (!node->value)
		return AST_ERR;

	return AST_OK;
}
