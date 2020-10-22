#ifndef TOKEN_RECOGNITION_H
#define TOKEN_RECOGNITION_H

#include <stdbool.h>

#include "token.h"

bool can_start_operator(char c);
bool can_form_operator(struct token *tok, char c, enum toktype *type);

#endif /* ! TOKEN_RECOGNITION_H */
