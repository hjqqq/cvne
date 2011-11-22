#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "defines.h"
#include "image.h"

struct Display
{
	int width;
	int height;
	ALLEGRO_DISPLAY* screen;
	struct Image** images;
};

struct Display* build_display(void);
int init_display(struct Display* display);
void free_display(struct Display* display);
void display_display(struct Display* display);

#endif

