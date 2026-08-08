#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mainparser.h"

static const char *flagi[] = {
    "-n",
    "-c"
};

int Flagparser(char **argv, int argc, size_t *line_number_mode, size_t *count_mode) {
    if (argc == 3) {
        return 0;
    }
    if (argc == 4) {
        size_t liczba_flag = sizeof(flagi) / sizeof(flagi[0]);
        for (size_t i = 0; i < liczba_flag; i++) {
            if (strcmp(argv[1], flagi[i]) == 0) {
                switch (i)
                {
                case 0:
                    (*line_number_mode)++;
                    return 0;
                case 1:
                    (*count_mode)++;
                    return 0;
                }
            }
        }
        return -1;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    size_t line_number_mode = 0;
    size_t count_mode = 0;

    if (Flagparser(argv, argc, &line_number_mode, &count_mode) != 0) {
        fprintf(stderr, "meep: Niepoprawna skladnia\n");
        exit(1);
    }

    mainparser(argv,line_number_mode,count_mode);

    return 0;
}

