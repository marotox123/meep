#ifndef TEKSTPARSER_H
#define TEKSTPARSER_H
#include "match.h"

int lineparser(char *buff, char *start, char *end, char *tekst, int mode);
int tekstparser(char *buff, int mode, char *tekst, MatchList *list);

#endif