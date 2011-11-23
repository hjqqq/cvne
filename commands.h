#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "game.h"
#include "defines.h"
#include "display.h"
#include "image.h"

struct Game;

struct CommandSet
{
	char text[MAX_COMMANDS][COMMAND_NAME_SIZE];
	void (*func[MAX_COMMANDS])(struct Game*, char*);
};

struct CommandSet* build_command_set(void);
void set_command(struct CommandSet* command_set, char* text, void (*func)(struct Game*, char*));
int run_command(struct Game* game, char* command);

void cmd_nothing(struct Game* game, char* arg);
void cmd_game_name(struct Game* game, char* arg);   
void cmd_width(struct Game* game, char* arg);
void cmd_height(struct Game* game, char* arg);
void cmd_go(struct Game* game, char* arg);
void cmd_display(struct Game* game, char* arg);
void cmd_load_image(struct Game* game, char* arg);
void cmd_close_image(struct Game* game, char* arg);
void cmd_move_image(struct Game* game, char* arg);
void cmd_set(struct Game* game, char* arg);

#endif

