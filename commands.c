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
	set_command(set, "game_name", cmd_game_name);
	set_command(set, "width", cmd_width);
	set_command(set, "height", cmd_height);
	set_command(set, "go", cmd_go);
	set_command(set, "display", cmd_display);
/*	set_command(set, "label", cmd_nothing);*/
	set_command(set, "load_image", cmd_load_image);
	set_command(set, "close_image", cmd_load_image);
	set_command(set, "move_image", cmd_move_image);
	set_command(set, "set", cmd_set);
	return set;
}

void set_command(struct CommandSet* command_set, char* text, void (*func)(struct Game*, char*))
{
	static int index = 0;
	strcpy(command_set->text[index], text);
	command_set->func[index] = func;
	index++;
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
	if(game->display->screen)
		strcpy(error, "cannot change window name is display already running");
	else
		strcpy(game->name, arg);
}

void cmd_width(struct Game* game, char* arg)
{
	if(game->display->screen)
		strcpy(error, "cannot change width is display already running");
	else
		game->display->width = atoi(arg);
}

void cmd_height(struct Game* game, char* arg)
{
	if(game->display->screen)
		strcpy(error, "cannot change height is display already running");
	else
		game->display->height = atoi(arg);
}

void cmd_go(struct Game* game, char* arg)
{
	/*char path[PATH_SIZE];*/
	if(game->file)
		fclose(game->file);
	/*strcpy(path, SCENES_PATH);
	strcpy(path + strlen(path), arg);*/
	path_compatibilize(arg);
	if(!(game->file = fopen(arg, "r")))
		sprintf(error, "cannot open \"%s\"", arg);
	printf("Going to file \"%s\"\n", arg);
}

void cmd_display(struct Game* game, char* arg)
{
	if(game->display->screen)
		strcpy(error, "display already initialized");
	else if(game->display->width <= 0)
		sprintf(error, "invalid or unset width : %d", game->display->width);
	else if(game->display->height <= 0)
		sprintf(error, "invalid or unset height : %d", game->display->height);
	else if(!init_display(game->display))
		strcpy(error, "cannot create display");
}

void cmd_load_image(struct Game* game, char* arg)
{
	char* filename = cut_command(arg);
	int id = atoi(arg);
	path_compatibilize(filename);
	if(image_id_in_range(id))
		if((game->display->images[id] = load_image(filename, 0, 0)) == NULL)
			sprintf(error, "cannot load image %d \"%s\"", id, filename);
}

void cmd_close_image(struct Game* game, char* arg)
{
	int id = atoi(arg);
	if(image_id_in_range(id))
		if(image_loaded(game->display->images, id))
			free_image(game->display->images[id]);
}

void cmd_move_image(struct Game* game, char* arg)
{
}

void cmd_set(struct Game* game, char* arg)
{
	replace_v_vars(game->vars, arg);;
}

