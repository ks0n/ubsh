#include <criterion/criterion.h>

#include "ast.h"
#include "ast/ast_value.h"

Test(ast, new_none)
{
    struct ast_node *node = ast_node_new(AST_NONE);

    cr_assert_null(node);
}

Test(ast, del_none)
{
    struct ast_node *node = ast_node_new(AST_NONE);
    cr_assert_eq(ast_node_del(node, AST_NONE), AST_NULL_PTR);
}

Test(ast, del_invalid_type)
{
    /* Create a new AST Value */
    struct ast_node *node = ast_node_new(AST_VALUE);

    /* But free it as if it was another AST Node type */
    int status = ast_node_del(node, AST_NONE);

    cr_assert_eq(status, AST_INVALID_TYPE);
}

Test(ast_value, new)
{
    struct ast_node *base_node = ast_node_new(AST_VALUE);
    struct ast_value *node = (struct ast_value *) base_node;

    cr_assert_null(node->value);

    cr_assert_eq(ast_node_del(UPCAST(node), AST_VALUE), AST_OK);
}

Test(ast_value, set_value)
{
    struct ast_node *base_node = ast_node_new(AST_VALUE);
    struct ast_value *node = (struct ast_value *) base_node;

    node->value = calloc(1, 256);
    memcpy(node->value, "ubsh", 4);

    cr_assert_eq(ast_node_del(UPCAST(node), AST_VALUE), AST_OK);
}
