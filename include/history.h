#ifndef SHELLFORGE_HISTORY_H
#define SHELLFORGE_HISTORY_H

#define HISTORY_MAX_ENTRIES 100
#define HISTORY_LINE_SIZE 256

typedef struct {
    char entries[HISTORY_MAX_ENTRIES][HISTORY_LINE_SIZE];
    int count;
} history_t;

void history_init(history_t *history);
void history_add(history_t *history, const char *line);
void history_print(const history_t *history);

#endif
