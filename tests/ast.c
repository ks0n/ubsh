#include <criterion/criterion.h>

#include "ast.h"
#include "ast/node_value.h"

Test(node_value, new)
{
	struct ast_node *base_node = get_node_value_base()->new();
	struct node_value *node = FROM_AST_NODE(base_node, struct node_value);

	cr_assert_null(node->value);

	CALL_AST_DEL(node);
}

Test(node_value, set_value)
{
	struct ast_node *base_node = get_node_value_base()->new();
	struct node_value *node = FROM_AST_NODE(base_node, struct node_value);

	node->value = calloc(1, 256);
	memcpy(node->value, "ubsh", 4);

	CALL_AST_DEL(node);
}

Test(node_value, exec_null_value)
{
	struct ast_node *base_node = get_node_value_base()->new();
	struct node_value *node = FROM_AST_NODE(base_node, struct node_value);

	cr_assert_eq(CALL_AST_EXEC(node), AST_OK);
	cr_assert_eq(CALL_AST_EXEC(node), AST_OK);

	CALL_AST_DEL(node);
}

Test(node_value, exec_non_null_value)
{
	struct ast_node *base_node = get_node_value_base()->new();
	struct node_value *node = FROM_AST_NODE(base_node, struct node_value);

	node->value = calloc(1, 256);
	memcpy(node->value, "ubsh", 4);

	cr_assert_eq(CALL_AST_EXEC(node), AST_OK);

	CALL_AST_DEL(node);
}
