#include <stdio.h>
#include <string.h>

#include "token.h"

void token_list_init(token_list_t *list)
{
    if (list != NULL) {
        list->count = 0;
    }
}

int token_add(token_list_t *list, token_type_t type, const char *text)
{
    token_t *token;

    if (list == NULL || list->count >= TOKEN_LIST_SIZE) {
        return -1;
    }

    token = &list->tokens[list->count++];
    token->type = type;
    if (text == NULL) {
        token->text[0] = '\0';
    } else {
        strncpy(token->text, text, sizeof(token->text) - 1);
        token->text[sizeof(token->text) - 1] = '\0';
    }
    return 0;
}

const char *token_name(token_type_t type)
{
    switch (type) {
    case TOKEN_WORD:       return "WORD";
    case TOKEN_PIPE:       return "PIPE";
    case TOKEN_INPUT:      return "INPUT";
    case TOKEN_OUTPUT:     return "OUTPUT";
    case TOKEN_APPEND:     return "APPEND";
    case TOKEN_BACKGROUND: return "BACKGROUND";
    case TOKEN_END:        return "END";
    default:               return "UNKNOWN";
    }
}

void token_print(const token_list_t *list)
{
    int i;

    if (list == NULL) {
        return;
    }

    printf("TOKENS\n");
    printf("%-5s %-12s %s\n", "INDEX", "TYPE", "TEXT");
    printf("----------------------------------------\n");
    for (i = 0; i < list->count; ++i) {
        printf("%-5d %-12s %s\n", i, token_name(list->tokens[i].type),
               list->tokens[i].text);
    }
}
