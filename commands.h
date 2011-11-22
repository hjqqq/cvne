#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "game.h"
#include "defines.h"

struct Game;

struct CommandSet
{
	char text[MAX_COMMANDS][COMMAND_NAME_SIZE];
	void (*func[MAX_COMMANDS])(struct Game*, char*);
};

struct CommandSet* build_command_set(void);
void set_command(struct CommandSet* command_set, int i, char* text, void (*func)(struct Game*, char*));
int run_command(struct Game* game, char* command);

void cmd_nothing(struct Game* game, char* arg);
void cmd_game_name(struct Game* game, char* arg);   
void cmd_width(struct Game* game, char* arg);
void cmd_height(struct Game* game, char* arg);
void cmd_go(struct Game* game, char* arg);
void cmd_display(struct Game* game, char* arg);

#endif

