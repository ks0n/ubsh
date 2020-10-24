#include "ast.h"

#include <stdlib.h>

static ast_node_new_f constructors[AST_TYPE_LEN] = { NULL };
static ast_node_del_f destructors[AST_TYPE_LEN] = { NULL };

struct ast_node *ast_node_new(enum ast_type type)
{
    if (!constructors[type])
        return NULL;

    struct ast_node *generic_node = constructors[type]();
    generic_node->type = type;

    return generic_node;
}

void ast_node_del(struct ast_node *node, enum ast_type type)
{
    if (!destructors[type])
        return;

    destructors[type](node);
}
