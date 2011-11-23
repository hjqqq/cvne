#include "display.h"

struct Display* build_display(void)
{
	struct Display* display = malloc(sizeof(struct Display));
	int i;
	display->screen = NULL;
	display->images = calloc(IMAGES, sizeof(struct Image*));
	for(i = 0; i < IMAGES; i++)
		display->images[i] = NULL;
	return display;
}

int init_display(struct Game* game)
{
	struct Var* width = get_var(game->vars, "width");
	struct Var* height = get_var(game->vars, "height");
	if(width)
	{
		if(height)
		{
			game->display->screen = al_create_display(width->value, height->value);
			return (int) game->display->screen;
		}
		else
			sprintf(error, "height unset");
	}
	else
		sprintf(error, "width unset");
	return 0;
}

void free_display(struct Display* display)
{
	int i;
	if(display->screen)
		al_destroy_display(display->screen);
	for(i = 0; i < IMAGES; i++)
		if(display->images[i])
			free_image(display->images[i]);
	free(display->images);
	free(display);
}

void display_display(struct Display* display)
{
	int i;
	al_set_target_bitmap(al_get_backbuffer(display->screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for(i = 0; i < IMAGES; i++)
		if(display->images[i])
			draw_image(display->images[i]);
	al_flip_display();
}

