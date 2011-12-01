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
	al_start_timer(timer);
	cmd_go(game, filename);
	while(!check_error())
	{
		ALLEGRO_EVENT event;
		if(al_get_next_event(game->event_queue, &event))
		{
			if(game->wait)
				game->wait(game, &event);
			switch(event.type)
			{
				case ALLEGRO_EVENT_TIMER:
					if(game->display->screen)
						display_display(game);
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					sprintf(error, "window closed");
					break;
				case ALLEGRO_EVENT_MOUSE_AXES:
					game->display->mousex = event.mouse.x;
					game->display->mousey = event.mouse.y;
					break;
			}
		}
		else if(game->wait)
			game->wait(game, NULL);
		if(!game->wait)
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
	struct Game* game = malloc(sizeof(struct Game));
	game->display = build_display();
	game->vars = build_special_vars(game);
	game->command_list = build_command_list();
	game->name[0] = '\0';
	game->wait_time = 0.0;
	game->file = NULL;
	game->wait = NULL;
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

