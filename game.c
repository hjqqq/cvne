#include "game.h"

void run_game(char* filename)
{
	struct Game* game = initialize_game();
	char buffer[BUFFER_SIZE];
	cmd_go(game, filename);
	printf("lol.\n");
	if(error[0] != '\0')
		printf("Error : \"%s\"\n", error);
	else
	{
		while(fgets(buffer, BUFFER_SIZE, game->file))
		{
			if(!run_command(game, strip_begin(buffer)))
			{
				printf("Error : \"%s\"\n", error);
				break;
			}
		}
	}
	printf("file ended.\n");
	free_game(game);
}

struct Game* initialize_game(void)
{
	int i;
	struct Game* game = malloc(sizeof(struct Game));
	game->display = build_display();
	game->display->images = calloc(IMAGES, sizeof(struct Image*));
	game->name[0] = '\0';
	for(i = 0; i < VARS; i++)
		game->vars[i] = 0;
/*	for(i = 0; i < LABELS; i++)
		game->labels[i] = pos;*/
	for(i = 0; i < IMAGES; i++)
		game->display->images[i] = NULL;
	game->file = NULL;
	game->command_set = build_command_set();
	return game;
}

void free_game(struct Game* game)
{
	if(game->file)
		fclose(game->file);
	if(game->display->screen)
		free_display(game->display);
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

int var_id_in_range(int id)
{
	return (id >= 0 && id < VARS);
}

