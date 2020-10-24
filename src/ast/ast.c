#include "ast.h"
#include "ast_value.h"

#include <stdlib.h>

static ast_node_new_f constructors[AST_TYPE_LEN] = {
    NULL,           /* AST_NONE */
    ast_value_new,  /* AST_VALUE */
};

static ast_node_del_f destructors[AST_TYPE_LEN] = {
    NULL,           /* AST_NONE */
    ast_value_del,  /* AST_VALUE */
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
