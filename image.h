#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "defines.h"
#include "display.h"

struct Image
{
	int x;
	int y;
	ALLEGRO_BITMAP* bitmap;
};

struct Image* load_image(char* filename);
void free_image(struct Image* image);
int image_id_in_range(int id);
int image_loaded(struct Image** images, int id);

#endif

