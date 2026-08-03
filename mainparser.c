#include <stdio.h>
#include <stdlib.h>
#include "tekstparser.h"
#include "match.h"

static void handle_output(MatchList *list, char *buff, int line_number_mode, int count_mode) {
    if (count_mode > 0) {
        printf("%zu\n", list->count);
    } else if (line_number_mode > 0) {
        for (Match *current = list->head; current != NULL; current = current->next) {
            printf("%zu: %s\n", current->line_number, current->line);
        }
    } else {
        for (Match *current = list->head; current != NULL; current = current->next) {
            printf("%s\n", current->line);
        }
    }
    match_list_free(list);
    free(buff);
    exit(0);
}

static char *handle_file(char *path) {
    FILE* fptr;
    fptr = fopen(path, "r");
    if (fptr == NULL) {
        perror("The file is not opened.");
        fclose(fptr);
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);

    rewind(fptr);

    char *buff = (char *)malloc(fileSize + 1);
    if (buff == NULL) {
        perror("Memory allocation failed");
        fclose(fptr);
        exit(1);
    }

    size_t bytesRead = fread(buff, 1, fileSize, fptr);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buff);
        fclose(fptr);
        exit(1);
    }

    buff[fileSize] = '\0';
    fclose(fptr);
    return buff;
}

void mainparser(char **argv, int line_number_mode, int count_mode) {
    int offset = (line_number_mode > 0 || count_mode > 0) ? 1 : 0;

    char *buff = handle_file(argv[2 + offset]);

    MatchList list = {
        .head = NULL,
        .tail = NULL,
        .count = 0
    };
    int result = tekstparser(buff, 0, argv[1 + offset], &list);

    handle_output(&list, buff, line_number_mode, count_mode);
}