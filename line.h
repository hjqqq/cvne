#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <allegro5/allegro.h>

#include "defines.h"
#include "game.h"

struct Line
{
	int pos;
	int width;
	char target[PATH_SIZE];
	ALLEGRO_BITMAP* bitmap;
	struct MessageBox* messagebox;
};

void add_line(struct MessageBox* messagebox, char* text, char* target);
void free_line(void* ptr);
void empty_lines(struct MessageBox* messagebox);

void cmd_clear_lines(struct Game* game, char* arg);

#endif

