#include "game.h"

void run_game(char* filename)
{
	struct Game game;
	char buffer[BUFFER_SIZE];
	initialize_game(&game);
	cmd_go(&game, filename);
	printf("lol.\n");
	if(error[0] != '\0')
		printf("Error : \"%s\"\n", error);
	else
	{
		while(fgets(buffer, BUFFER_SIZE, game.file))
		{
			if(!run_command(&game, strip_begin(buffer)))
			{
				printf("Error : \"%s\"\n", error);
				break;
			}
		}
	}
	printf("file ended.\n");
	free_game(&game);
}

void initialize_game(struct Game* game)
{
	int i;
	game->width = 0;
	game->height = 0;
	game->name[0] = '\0';
	for(i = 0; i < VARS; i++)
		game->vars[i] = 0;
/*	for(i = 0; i < LABELS; i++)
		game->labels[i] = pos;*/
	game->file = NULL;
	game->command_set = build_command_set();
}

void free_game(struct Game* game)
{
	if(game->file)
		fclose(game->file);
	free(game->command_set);
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

