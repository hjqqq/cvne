#include "display.h"

struct Display* build_display(void)
{
	struct Display* display = malloc(sizeof(struct Display));
	int i;
	display->screen = NULL;
	display->sounds = calloc(SOUNDS, sizeof(struct Sound*));
	for(i = 0; i < IMAGES; i++)
	{
		display->images[i].x = 0;
		display->images[i].y = 0;
		display->images[i].bitmap = NULL;
	}
	for(i = 0; i < SOUNDS; i++)
		display->sounds[i] = NULL;
	display->messagebox = init_messagebox();
	return display;
}

void init_display(struct Game* game)
{
	game->display->screen = al_create_display(*game->display->width, *game->display->height);
	if(game->display->screen)
	{
		al_register_event_source(game->event_queue,
			al_get_display_event_source(game->display->screen));
		al_register_event_source(game->event_queue,
			al_get_mouse_event_source());
		al_register_event_source(game->event_queue,
			al_get_keyboard_event_source());
	}
	else
		sprintf(error, "cannot create display of size %d x %d",
			*game->display->width, *game->display->height);
}

void free_display(struct Display* display)
{
	int i;
	if(display->screen)
		al_destroy_display(display->screen);
	for(i = 0; i < IMAGES; i++)
		if(display->images[i].bitmap)
			al_destroy_bitmap(display->images[i].bitmap);
	for(i = 0; i < SOUNDS; i++)
		if(display->sounds[i])
			freestop_sound(display->sounds[i]);
	free(display->sounds);
	free_messagebox(display->messagebox);
	free(display);
}

void display_display(struct Game* game)
{
	int i;
	struct Display* display = game->display;
	al_set_target_bitmap(al_get_backbuffer(display->screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if(display->messagebox->display && *display->messagebox->image < 0)
		draw_messagebox(display->messagebox);
	for(i = 0; i < IMAGES; i++)
	{
		if(display->images[i].bitmap != NULL)
		{
			if(i == *display->messagebox->image)
			{
				if(display->messagebox->display)
				{
					draw_image(&display->images[i]);
					draw_messagebox(display->messagebox);
				}
			}
			else if(i == *display->messagebox->choicecursor)
			{
				if(display->messagebox->display)
					draw_cursor(&display->images[i], display);
			}
			else
				draw_image(&display->images[i]);
		}
	}
	if(display->messagebox->display && *display->messagebox->image >= IMAGES)
		draw_messagebox(display->messagebox);
	al_flip_display();
}

void cmd_display(struct Game* game, char* arg)
{
	if(game->display->screen)
		strcpy(error, "display already initialized");
	else
		init_display(game);
}

