#include <ctype.h>
#include <stddef.h>

#include "lexer.h"

static int append_char(char *word, size_t *length, char c)
{
    if (*length >= TOKEN_TEXT_SIZE - 1) {
        return -1;
    }
    word[(*length)++] = c;
    return 0;
}

static int add_operator(token_list_t *list, token_type_t type, const char *text)
{
    return token_add(list, type, text);
}

int lexer(const char *input, token_list_t *list)
{
    const char *p;
    char word[TOKEN_TEXT_SIZE];
    size_t length;

    if (input == NULL || list == NULL) {
        return -1;
    }
    token_list_init(list);
    p = input;

    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            ++p;
        }
        if (*p == '\0') {
            break;
        }

        if (*p == '|' || *p == '<' || *p == '>' || *p == '&') {
            if (*p == '|') {
                if (add_operator(list, TOKEN_PIPE, "|") != 0) return -1;
            } else if (*p == '<') {
                if (add_operator(list, TOKEN_INPUT, "<") != 0) return -1;
            } else if (*p == '>') {
                if (p[1] == '>') {
                    if (add_operator(list, TOKEN_APPEND, ">>") != 0) return -1;
                    ++p;
                } else if (add_operator(list, TOKEN_OUTPUT, ">") != 0) {
                    return -1;
                }
            } else if (add_operator(list, TOKEN_BACKGROUND, "&") != 0) {
                return -1;
            }
            ++p;
            continue;
        }

        length = 0;
        while (*p != '\0' && !isspace((unsigned char)*p) &&
               *p != '|' && *p != '<' && *p != '>' && *p != '&') {
            if (*p == '\\') {
                if (p[1] == '\0') {
                    return -1;
                }
                if (append_char(word, &length, p[1]) != 0) return -1;
                p += 2;
            } else if (*p == '\'' || *p == '\"') {
                char quote = *p++;
                while (*p != '\0' && *p != quote) {
                    if (*p == '\\' && quote == '\"' && p[1] != '\0') {
                        if (append_char(word, &length, p[1]) != 0) return -1;
                        p += 2;
                    } else {
                        if (append_char(word, &length, *p++) != 0) return -1;
                    }
                }
                if (*p != quote) {
                    return -1;
                }
                ++p;
            } else {
                if (append_char(word, &length, *p++) != 0) return -1;
            }
        }
        word[length] = '\0';
        if (token_add(list, TOKEN_WORD, word) != 0) {
            return -1;
        }
    }

    return token_add(list, TOKEN_END, "");
}
