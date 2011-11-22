#include "commands.h"

struct CommandSet* build_command_set(void)
{
	struct CommandSet* set = malloc(sizeof(struct CommandSet));
	int i;

	for(i = 0; i < MAX_COMMANDS; i++)
	{
		set->text[i][0] = '\0';
		set->func[i] = cmd_nothing;
	}
	set_command(set, 0, "game_name", cmd_game_name);
	set_command(set, 1, "width", cmd_width);
	set_command(set, 2, "height", cmd_height);
	set_command(set, 3, "go", cmd_go);
	set_command(set, 4, "display", cmd_display);
/*	set_command(set, 5, "label", cmd_nothing);*/
	return set;
}

void set_command(struct CommandSet* command_set, int i, char* text, void (*func)(struct Game*, char*))
{
	strcpy(command_set->text[i], text);
	command_set->func[i] = func;
}

int run_command(struct Game* game, char* command)
{
	if(command[0] != '\0' && command[0] != '\n' && command[0] != '#')
	{
		int i;
		char* arg = cut_command(command);
		printf("Running \"%s\" \"%s\"\n", command, arg);
		for(i = 0; i < MAX_COMMANDS; i++)
		{
			if(strcmp(command, game->command_set->text[i]) == 0)
			{
				game->command_set->func[i](game, arg);
				return !(error[0] != '\0');
			}
		}
		if(i == MAX_COMMANDS)
		{
			sprintf(error, "unknown command : %s", command);
			return 0;
		}
	}
	return 1;
}
	
void cmd_nothing(struct Game* game, char* arg)
{
}

void cmd_game_name(struct Game* game, char* arg)
{
	strcpy(game->name, arg);
}

void cmd_width(struct Game* game, char* arg)
{
	game->width = atoi(arg);
}

void cmd_height(struct Game* game, char* arg)
{
	game->height = atoi(arg);
}

void cmd_go(struct Game* game, char* arg)
{
	char path[PATH_SIZE];
	if(game->file)
		fclose(game->file);
	strcpy(path, SCENES_PATH);
	strcpy(path + strlen(path), arg);
	if(!(game->file = fopen(path, "r")))
		sprintf(error, "cannot open \"%s\"", path);
	printf("Going to file \"%s\"\n", arg);
}

void cmd_display(struct Game* game, char* arg)
{
	if(game->width <= 0)
		sprintf(error, "invalid or unset width : %d", game->width);
	else if(game->height <= 0)
		sprintf(error, "invalid or unset height : %d", game->height);
	else if(game->name[0] == '\0')
		sprintf(error, "invalid or unset name : \"\"");
	else
		printf("cool, can display.\n");
}

