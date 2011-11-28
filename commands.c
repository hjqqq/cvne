#include "commands.h"

void build_command_list(struct Item* list)
{	
	add_command(list, "game_name", cmd_game_name);
	add_command(list, "go", cmd_go);
	add_command(list, "display", cmd_display);
	add_command(list, "load_image", cmd_load_image);
	add_command(list, "close_image", cmd_load_image);
	add_command(list, "move_image", cmd_move_image);
	add_command(list, "set", cmd_set);
	add_command(list, "goif", cmd_goif);
	add_command(list, "wait", cmd_wait);
	add_command(list, "play_sound", cmd_play_sound);
	add_command(list, "play_sound_loop", cmd_play_sound_loop);
	add_command(list, "stop_sound", cmd_stop_sound);
	add_command(list, "message", cmd_message);
	add_command(list, "show_message", cmd_show_message);
}

void add_command(struct Item* list, char* text, void (*func)(struct Game*, char*))
{
	struct Command* command = malloc(sizeof(struct Command));
	strcpy(command->text, text);
	command->func = func;
	add_after(list, command);
}

int run_command(struct Game* game, char* command)
{
	if(command[0] != '\0' && command[0] != '\n' && command[0] != '#')
	{
		char* arg = cut_command(command);
		struct Item* cur = game->command_list;
		if(*game->verbose)
			printf("[%s%s %s%s%s] ", TBLUE, command, TYELLOW, arg, TDEF);
		while(cur)
		{
			if(strcmp(command, ((struct Command*)cur->val)->text) == 0)
			{
				((struct Command*)cur->val)->func(game, arg);
				if(*game->verbose)
					printf("\n");
				return !(error[0] != '\0');
			}
			cur = cur->next;
		}
		sprintf(error, "unknown command : %s", command);
		if(*game->verbose)
			printf("\n");
		return 0;
	}
	return 1;
}
	
void cmd_nothing(struct Game* game, char* arg)
{
	if(*game->verbose)
		printf("doing absolutely fucking %snothing%s", TCYAN, TDEF);
}

void cmd_game_name(struct Game* game, char* arg)
{
	strcpy(game->name, arg);
}

void cmd_go(struct Game* game, char* arg)
{
	if(game->file)
		fclose(game->file);
	path_compatibilize(arg);
	if(strcmp(arg, "-") == 0)
	{
		game->file = stdin;
		if(*game->verbose)
			printf("--> \"%s%s%s\"", TMAGENTA, arg, TDEF);
	}
	else if(!(game->file = fopen(arg, "r")))
		sprintf(error, "cannot open \"%s\"", arg);
	else if(*game->verbose)
		printf("--> \"%s%s%s\"", TMAGENTA, arg, TDEF);
}

void cmd_goif(struct Game* game, char* arg)
{
	char* filename = cut_command(arg);
	if(eval(game->vars, arg))
		cmd_go(game, filename);
}

void cmd_wait(struct Game* game, char* arg)
{
	double time = atof(arg);
	game->wait_time = al_get_time() + time;
	game->wait = waitfortime;
	if(*game->verbose)
		printf("waiting %s%f%s seconds", TMAGENTA, time, TDEF);
}

