#ifndef PARSER_H
#define PARSER_H

#include "ast/ast.h"
#include "lexer.h"

int parser_parse(struct ast_node **root, struct lexer *l);

#endif /* ! PARSER_H */
