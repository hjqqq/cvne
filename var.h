#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "defines.h"
#include "data.h"

struct Game;

struct Var
{
	char name[VAR_NAME_SIZE];
	int value;
};

struct Var* get_var(struct Item* list, char* name);
struct Var* set_var(struct Item* list, char* name, int value);
void replace_vars_values(struct Item* vars, char* s);
int* setbind(struct Item* list, char* name, int value);
struct Item* build_special_vars(struct Game* game);
ALLEGRO_COLOR get_color_var(ALLEGRO_COLOR* colors, int id, ALLEGRO_COLOR defaultval);

void cmd_set(struct Game* game, char* arg);

#endif

