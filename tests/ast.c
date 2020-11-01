#include <criterion/criterion.h>

#include "ast/ast.h"
#include "ast/node_value.h"

struct node_value *g_node;

void setup_node_value(void)
{
	struct ast_node *generic_node = get_node_value_methods()->new ();
	g_node = FROM_AST_NODE(generic_node, struct node_value);
}

void teardown_node_value(void)
{
	CALL_AST_DEL(g_node);
}

Test(node_value, new, .init = setup_node_value, .fini = teardown_node_value)
{
	cr_assert_null(g_node->value);
}

Test(node_value, set_value, .init = setup_node_value,
     .fini = teardown_node_value)
{
	g_node->value = calloc(1, 256);
	memcpy(g_node->value, "ubsh", 4);
}

Test(node_value, exec_null_value, .init = setup_node_value,
     .fini = teardown_node_value)
{
	cr_assert_eq(CALL_AST_EXEC(g_node), AST_OK);
	cr_assert_eq(CALL_AST_EXEC(g_node), AST_OK);
}

Test(node_value, exec_non_null_value, .init = setup_node_value,
     .fini = teardown_node_value)
{
	g_node->value = calloc(1, 256);
	memcpy(g_node->value, "ubsh", 4);

	cr_assert_eq(CALL_AST_EXEC(g_node), AST_OK);
}
