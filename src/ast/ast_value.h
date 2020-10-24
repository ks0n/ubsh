#include "ast.h"

struct ast_value {
	struct ast_node base;

	char *value;
};

AST_CONSTRUCTOR(ast_value_new);
AST_DESTRUCTOR(ast_value_del, node);
AST_EXECUTOR(ast_value_exec, node);
