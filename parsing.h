#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include "commands.h"
#include "data.h"

char* cut_command(char* buffer);
int skip_space(char* s, int i);
int skip_to_space(char* s, int i);
char* strip_begin(char* s);
void path_compatibilize(char* path);
int eval(struct Item* vars, char* s);
void remove_spaces(char* s);
void check_expr(char* s);
ALLEGRO_COLOR str_to_color(char* s);

#endif

