#include <stdio.h>
#include <stdlib.h>
#include "tekstparser.h"
#include "match.h"
void mainparser(char **argv, int line_number_mode, int count_mode) {
    FILE* fptr;
    if (line_number_mode > 0 || count_mode > 0) {
        printf("Z flaga wykonano\n");
        fclose(fptr);
        exit(0);
    }
    fptr = fopen(argv[2], "r");
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
    MatchList list = {
        .head = NULL,
        .tail = NULL,
        .count = 0
    };
    int result = tekstparser(buff, 0, argv[1], &list);

    for (Match *current = list.head; current != NULL; current = current->next) {
        printf("%s\n",current->line);
    }
    match_list_free(&list);
    free(buff);
    exit(0);
}