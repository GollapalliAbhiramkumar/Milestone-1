#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "history.h"
#include "lexer.h"

int main(void) {
    history_t command_history;
    token_list_t tokens;

    history_init(&command_history);
    printf("========================================\n");
    printf("ShellForge\n");
    printf("A Unix Style Shell written in C\n");
    printf("========================================\n");

    char *line;
    while (1) {
        line = readline("shellforge$ ");
        if (line == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        if (line[0] == '\0') {
            free(line);
            continue;
        }

        add_history(line);
        history_add(&command_history, line);

        if (strcmp(line, "exit") == 0) {
            free(line);
            printf("Exiting...\n");
            break;
        }

        if (strcmp(line, "history") == 0) {
            history_print(&command_history);
        } else if (lexer(line, &tokens) != 0) {
            fprintf(stderr, "Lexer error: unmatched quote, trailing escape, or token limit exceeded.\n");
        } else {
            token_print(&tokens);
        }
        free(line);
    }
    return 0;
}
