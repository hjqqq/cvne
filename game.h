#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "parsing.h"
#include "commands.h"
#include "display.h"
#include "data.h"
#include "termcolor.h"

char error[ERROR_SIZE];

struct Var
{
	char name[VAR_NAME_SIZE];
	int value;
};

struct Game
{
	struct Display* display;
	char name[NAME_SIZE];
	struct Item* vars;
	FILE* file;
	struct Item* command_list;
};

void run_game(char* filename);
struct Game* initialize_game(void);
void free_game(struct Game* game);
struct Var* get_var(struct Item* list, char* name);
void set_var(struct Item* list, char* name, int value);
void termcolor(char* s);

#endif

