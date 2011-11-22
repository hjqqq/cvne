#include "display.h"

struct Display* build_display(void)
{
	struct Display* display = malloc(sizeof(struct Display));
	int i;
	display->width = 0;
	display->height = 0;
	display->screen = NULL;
	display->images = calloc(IMAGES, sizeof(struct Image*));
	for(i = 0; i < IMAGES; i++)
		display->images[i] = NULL;
	return display;
}

int init_display(struct Display* display)
{
	display->screen = al_create_display(display->width, display->height);
	return (int) display->screen;
}

void free_display(struct Display* display)
{
	int i;
	al_destroy_display(display->screen);
	for(i = 0; i < IMAGES; i++)
		if(display->images[i])
			free_image(display->images[i]);
	free(display->images);
	free(display);
}

void display_display(struct Display* display)
{
	al_set_target_bitmap(al_get_backbuffer(display->screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

