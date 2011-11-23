#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "game.h"
#include "defines.h"
#include "image.h"

struct Game;

struct Display
{
	ALLEGRO_DISPLAY* screen;
	struct Image** images;
};

struct Display* build_display(void);
int init_display(struct Game* game);
void free_display(struct Display* display);
void display_display(struct Display* display);

#endif

