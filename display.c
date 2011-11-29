#include "display.h"

struct Display* build_display(void)
{
	struct Display* display = malloc(sizeof(struct Display));
	int i;
	display->screen = NULL;
	display->images = calloc(IMAGES, sizeof(struct Image*));
	display->sounds = calloc(SOUNDS, sizeof(struct Sound*));
	display->colors = calloc(COLORS, sizeof(struct Color));
	for(i = 0; i < IMAGES; i++)
		display->images[i] = NULL;
	for(i = 0; i < SOUNDS; i++)
		display->sounds[i] = NULL;
	for(i = 0; i < COLORS; i++)
	{
		display->colors[i].r = 0;
		display->colors[i].g = 0;
		display->colors[i].b = 0;
		display->colors[i].a = 0;
	}
	display->font = al_load_ttf_font(FONT_FILE, DEFAULT_FONT_SIZE, 0);
	if(!display->font)
		sprintf(error, "cannot load font file \"%s\"", FONT_FILE);
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
		game->display->messagebox = init_messagebox(game->display->font);
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
		if(display->images[i])
			free_image(display->images[i]);
	for(i = 0; i < SOUNDS; i++)
		if(display->sounds[i])
			freestop_sound(display->sounds[i]);
	free(display->images);
	free(display->sounds);
	free(display->colors);
	al_destroy_font(display->font);
	free(display);
}

void display_display(struct Game* game)
{
	int i;
	struct Display* display = game->display;
	al_set_target_bitmap(al_get_backbuffer(display->screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for(i = 0; i < IMAGES; i++)
		if(display->images[i] != 0 && i != display->messagebox->image)
			draw_image(display->images[i]);
	if(display->messagebox->display)
	{
		struct MessageBox* messagebox = display->messagebox;
		struct Item* cur = messagebox->lines;
		if(messagebox->image >= 0 && messagebox->image < IMAGES)
			draw_image(display->images[i]);
		while(cur)
		{
			al_draw_text(display->font, al_map_rgb(0, 255, 255),
				*messagebox->x,
				(*messagebox->y) + messagebox->lineheight * ((struct Line*)cur->val)->pos,
				0,
				((struct Line*)cur->val)->text);
			cur = cur->next;
		}
	}
	al_flip_display();
}

void cmd_display(struct Game* game, char* arg)
{
	if(game->display->screen)
		strcpy(error, "display already initialized");
	else
		init_display(game);
}

