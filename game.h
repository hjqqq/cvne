#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <allegro5/allegro.h>

#include "defines.h"
#include "parsing.h"
#include "commands.h"
#include "display.h"
#include "data.h"
#include "termcolor.h"

char error[ERROR_SIZE];

struct Game
{
	struct Display* display;
	char name[NAME_SIZE];
	struct Item* vars;
	FILE* file;
	struct Item* command_list;
	int* verbose;
	int mousex;
	int mousey;
	ALLEGRO_EVENT_QUEUE* event_queue;
	void (*wait)(struct Game*, ALLEGRO_EVENT*);
	double wait_time;
};

int check_error(void);
void run_game(char* filename);
struct Game* initialize_game(void);
void free_game(struct Game* game);

#endif

