#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "parsing.h"
#include "commands.h"

char error[ERROR_SIZE];

struct Game
{
	int width;
	int height;
	char name[NAME_SIZE];
	int vars[VARS];
	FILE* file;
	struct CommandSet* command_set;
/*	fpos_t labels[LABELS];*/
};

void run_game(char* filename);
void initialize_game(struct Game* game);
void free_game(struct Game* game);
/*void load_labels(struct Game* game);*/

#endif

