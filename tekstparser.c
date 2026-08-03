#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "match.h"

int lineparser(char *buff, char *start, char *end, char *tekst, int mode) {
    char *ptr = start;
    size_t k = 0;
    size_t tekst_lenght = strlen(tekst);
    while (ptr < end) {
        k = 0;
        char *p2 = ptr;
        for (int j = 0; p2 < end && tekst[j] != '\0' && *p2 == tekst[j]; j++, p2++) {
            k++;
        }
        if (k >= tekst_lenght) {
            return 0;
        }
        ptr++;
    }
    return 1;
}

int tekstparser(char *buff, int mode, char *tekst, MatchList *list)
{
    char *startline = buff;
    char *endline = NULL;
    size_t line_number = 1;

    for (char *p = buff; ; p++) {
        if (*p == '\n' || *p == '\0') {
            endline = p;

            if (lineparser(buff, startline, endline, tekst, mode) == 0) {
                size_t length = (size_t)(endline - startline);

                char *result = malloc(length + 1);
                if (result == NULL) {
                    return -1;
                }

                memcpy(result, startline, length);
                result[length] = '\0';

                Match *node = match_create(result, line_number);
                if (node == NULL) {
                    free(result);
                    return -1;
                }

                match_append(list, node);
            }

            if (*p == '\0') {
                return 0;
            }

            startline = p + 1;
            line_number++;
        }
    }
}

