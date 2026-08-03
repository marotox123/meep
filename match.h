#ifndef MATCH_H
#define MATCH_H
#include <stddef.h>

typedef struct Match {
    char *line;
    size_t line_number;
    struct Match *next;
} Match;

typedef struct {
    Match *head;
    Match *tail;
    size_t count;
} MatchList;

Match *match_create(char *line, size_t line_number);
void match_append(MatchList *list, Match *node);
void match_print(Match *head);
void match_free(Match *head);
void match_list_free(MatchList *list);

#endif
