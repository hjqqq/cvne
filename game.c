#include "game.h"

int check_error(void)
{
	if(error[0] != '\0')
	{
		fprintf(stderr, "[%serror%s] %s%s%s\n", TRED, TDEF, TRED, error, TDEF);
		return 1;
	}
	return 0;
}

void run_game(char* filename)
{
	struct Game* game = initialize_game();
	char buffer[BUFFER_SIZE];
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
	game->event_queue = al_create_event_queue();
	al_register_event_source(game->event_queue, al_get_timer_event_source(timer));
	al_register_event_source(game->event_queue, al_get_mouse_event_source());
	al_start_timer(timer);
	cmd_go(game, filename);
	if(*game->verbose) printf("\n");
	while(!check_error())
	{
		ALLEGRO_EVENT event;
		if(al_get_next_event(game->event_queue, &event))
		{
			switch(event.type)
			{
				case ALLEGRO_EVENT_TIMER:
					if(game->display->screen)
						display_display(game->display);
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					sprintf(error, "window closed");
					break;
			}
		}
		if(!game->waiting)
			game->wait_event(game, &event);
		else if(al_get_time() > game->wait_time)
		{
			if(!fgets(buffer, BUFFER_SIZE, game->file))
				break;
			run_command(game, strip_begin(buffer));
		}
	}
	al_destroy_timer(timer);
	al_destroy_event_queue(game->event_queue);
	free_game(game);
}

struct Game* initialize_game(void)
{
	int i;
	struct Game* game = malloc(sizeof(struct Game));
	game->display = build_display();
	game->display->images = calloc(IMAGES, sizeof(struct Image*));
	game->name[0] = '\0';
	game->wait_time = 0.0;
	game->vars = build_first_item(malloc(sizeof(struct Var)));
	strcpy(((struct Var*)game->vars->val)->name, VERBOSE_VAR);
	((struct Var*)game->vars->val)->value = 1;
	game->verbose = &(((struct Var*)game->vars->val)->value);
	for(i = 0; i < IMAGES; i++)
		game->display->images[i] = NULL;
	game->file = NULL;
	game->waiting = 0;
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

