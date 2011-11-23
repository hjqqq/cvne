#include "game.h"

void run_game(char* filename)
{
	struct Game* game = initialize_game();
	char buffer[BUFFER_SIZE];
	printf("[ ] ");
	cmd_go(game, filename);
	printf("\n");
	if(error[0] != '\0')
		printf("[%serror%s] %s%s%s\n", TRED, TDEF, TRED, error, TDEF);
	else
	{
		while(fgets(buffer, BUFFER_SIZE, game->file))
		{
			if(!run_command(game, strip_begin(buffer)))
			{
				printf("[%serror%s] %s%s%s\n", TRED, TDEF, TRED, error, TDEF);
				break;
			}
		}
	}
	printf("[ ] file ended.\n");
	free_game(game);
}

struct Game* initialize_game(void)
{
	int i;
	struct Game* game = malloc(sizeof(struct Game));
	game->display = build_display();
	game->display->images = calloc(IMAGES, sizeof(struct Image*));
	game->name[0] = '\0';
	game->vars = build_first_item(malloc(sizeof(struct Var)));
	strcpy(((struct Var*)game->vars->val)->name, "null");
	((struct Var*)game->vars->val)->value = 0;
	for(i = 0; i < IMAGES; i++)
		game->display->images[i] = NULL;
	game->file = NULL;
	game->command_list = build_first_item(malloc(sizeof(struct Command)));
	strcpy(((struct Command*)game->command_list->val)->text, "nothing");
	((struct Command*)game->command_list->val)->func = cmd_nothing;
	build_command_list(game->command_list);
	return game;
}

void free_game(struct Game* game)
{
	if(game->file)
		fclose(game->file);
	free_display(game->display);
	free_list(game->command_list, free);
	free_list(game->vars, free);
	free(game);
}

/*void load_labels(struct Game* game)
{
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, BUFFER_SIZE, game->file))
	{
		char* command = strip_begin(buffer);
		if(strcmp(command, "label") == 0)
		{
			char* arg = cut_command(command);
			int label = atoi(arg);
			if(label < LABELS)
				fgetpos(game->file, &(game->labels[label]));
		}
	}
}*/

struct Var* get_var(struct Item* list, char* name)
{
	while(list)
	{
		if(strcmp(((struct Var*)list->val)->name, name) == 0)
			return (struct Var*)list->val;
		list = list->next;
	}
	return NULL;
}

void set_var(struct Item* list, char* name, int value)
{
	struct Var* var = get_var(list, name);
	if(!var)
	{
		var = malloc(sizeof(struct Var));
		strcpy(var->name, name);
		add_after(list, var);
	}
	var->value = value;
}

/* Colors :
 *  0		default
 *  5		blink
 *  Foreground :	30		31		32		33		34		35		36		37
 *  Background :	40		41		42		43		44		45		46		47
 *	For colors :	black	red		green	yellow	blue	magenta	cyan	white
 */
void termcolor(char* s)
{
	printf("\033[%sm", s);
}

