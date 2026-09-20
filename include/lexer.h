#ifndef SHELLFORGE_LEXER_H
#define SHELLFORGE_LEXER_H

#include "token.h"

/* Returns 0 on success and -1 for malformed or oversized input. */
int lexer(const char *input, token_list_t *list);

#endif
