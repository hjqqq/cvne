#ifndef MESSAGEBOX_H_INCLUDED
#define MESSAGEBOX_H_INCLUDED

#include <allegro5/allegro.h>

#include "defines.h"
#include "game.h"

struct MessageBox
{
	ALLEGRO_COLOR colors[COLORS];
	int i;
	struct Item* lines;
	int display;
	int lineheight;
	int* message_color;
	int* choice_color;
	int* message_bg_color;
	int* choice_bg_color;
	int* image;
	int* choicecursor;
	int* x;
	int* y;
	ALLEGRO_FONT* font;
};

struct MessageBox* init_messagebox(void);
void free_messagebox(struct MessageBox* messagebox);
void draw_messagebox(struct MessageBox* messagebox);

void cmd_set_font(struct Game* game, char* arg);
void cmd_set_color(struct Game* game, char* arg);

#endif

