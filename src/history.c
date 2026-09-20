#include <stdio.h>
#include <string.h>

#include "history.h"

void history_init(history_t *history)
{
    if (history != NULL) {
        history->count = 0;
    }
}

void history_add(history_t *history, const char *line)
{
    int i;

    if (history == NULL || line == NULL || line[0] == '\0') {
        return;
    }

    if (history->count == HISTORY_MAX_ENTRIES) {
        for (i = 1; i < HISTORY_MAX_ENTRIES; ++i) {
            memcpy(history->entries[i - 1], history->entries[i], HISTORY_LINE_SIZE);
        }
        --history->count;
    }

    strncpy(history->entries[history->count], line, HISTORY_LINE_SIZE - 1);
    history->entries[history->count][HISTORY_LINE_SIZE - 1] = '\0';
    ++history->count;
}

void history_print(const history_t *history)
{
    int i;

    if (history == NULL) {
        return;
    }
    for (i = 0; i < history->count; ++i) {
        printf("%d  %s\n", i + 1, history->entries[i]);
    }
}
