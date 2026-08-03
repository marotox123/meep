#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mainparser.h"
int main(int argc, char *argv[]) {
    size_t line_number_mode = 0;
    size_t count_mode = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        line_number_mode++;
    }else if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        count_mode++;
    }

    mainparser(argv,line_number_mode,count_mode);
    
    return 0;
}