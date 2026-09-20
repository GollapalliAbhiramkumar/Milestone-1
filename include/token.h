#ifndef SHELLFORGE_TOKEN_H
#define SHELLFORGE_TOKEN_H

#define TOKEN_TEXT_SIZE 256
#define TOKEN_LIST_SIZE 128

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_INPUT,
    TOKEN_OUTPUT,
    TOKEN_APPEND,
    TOKEN_BACKGROUND,
    TOKEN_END
} token_type_t;

typedef struct {
    token_type_t type;
    char text[TOKEN_TEXT_SIZE];
} token_t;

typedef struct {
    token_t tokens[TOKEN_LIST_SIZE];
    int count;
} token_list_t;

void token_list_init(token_list_t *list);
int token_add(token_list_t *list, token_type_t type, const char *text);
const char *token_name(token_type_t type);
void token_print(const token_list_t *list);

#endif
