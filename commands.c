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
		printf("[%s%s %s%s%s] ", TBLUE, command, TYELLOW, arg, TDEF);
		while(cur)
		{
			if(strcmp(command, ((struct Command*)cur->val)->text) == 0)
			{
				((struct Command*)cur->val)->func(game, arg);
				printf("\n");
				return !(error[0] != '\0');
			}
			cur = cur->next;
		}
		sprintf(error, "unknown command : %s", command);
		return 0;
	}
	return 1;
}
	
void cmd_nothing(struct Game* game, char* arg)
{
	printf("doing absolutely fucking %snothing%s", TMAGENTA, TDEF);
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
		game->file = stdin;
	else if(!(game->file = fopen(arg, "r")))
		sprintf(error, "cannot open \"%s\"", arg);
	else
		printf("--> \"%s%s%s\"", TMAGENTA, arg, TDEF);
}

void cmd_display(struct Game* game, char* arg)
{
	if(game->display->screen)
		strcpy(error, "display already initialized");
	else if(!init_display(game))
		strcpy(error, "cannot create display");
}

void cmd_load_image(struct Game* game, char* arg)
{
	char* filename = cut_command(arg);
	int id = atoi(arg);
	path_compatibilize(filename);
	if(image_id_in_range(id))
		if((game->display->images[id] = load_image(filename, 0, 0)) == NULL)
			sprintf(error, "cannot load image %s%d%s \"%s%s%s\"",
				TMAGENTA, id, TDEF, TMAGENTA, filename, TDEF);
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
	char* valuestr = cut_command(arg);
	int value = eval(game->vars, valuestr);
	set_var(game->vars, arg, value);
	printf("%s%s%s = %s%d%s", TGREEN, arg, TDEF, TMAGENTA, value, TDEF);
}

