#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "game.h"
#include "defines.h"
#include "display.h"
#include "image.h"
#include "data.h"
#include "interface.h"

struct Game;

struct Command
{
	char text[COMMAND_NAME_SIZE];
	void (*func)(struct Game*, char*);
};

struct Item* build_command_list(void);
void add_command(struct Item* list, char* text, void (*func)(struct Game*, char*));
int run_command(struct Game* game, char* command);

void cmd_nothing(struct Game* game, char* arg);
void cmd_game_name(struct Game* game, char* arg);   
void cmd_go(struct Game* game, char* arg);
void cmd_goif(struct Game* game, char* arg);
void cmd_wait(struct Game* game, char* arg);

#endif

