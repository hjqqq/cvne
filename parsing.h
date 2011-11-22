#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include "commands.h"

char* cut_command(char* buffer);
int skip_space(char* s, int i);
int skip_to_space(char* s, int i);
char* strip_begin(char* s);
void path_compatibilize(char* path);

#endif

