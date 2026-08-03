#include <stdlib.h>
#include "match.h"

Match *match_create(char *line, size_t line_number) {
    Match *node = malloc(sizeof(Match));

    if (node == NULL) {
        return NULL;
    }

    node->line = line;
    node->line_number = line_number;
    node->next = NULL;

    return node;
}

void match_append(MatchList *list, Match *node)
{
    if (list == NULL || node == NULL) {
        return;
    }

    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->count++;
}

void match_print(Match *head) {
}

void match_free(Match *head) {
}

void match_list_free(MatchList *list)
{
    Match *current = list->head;

    while (current != NULL) {
        Match *next = current->next;

        free(current->line);
        free(current);

        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}
