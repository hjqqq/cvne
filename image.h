#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "defines.h"
#include "display.h"

/*struct ChangingValue
{
	float value;
	double starttime;
	float startvalue;
	double endtime;
	float endvalue;
};*/

struct Image
{
	int id;
	ALLEGRO_BITMAP* bitmap;
	float x;
	float y;
};

struct Image* load_image(char* filename, float x, float y);
void free_image(struct Image* image);
int image_id_in_range(int id);
int image_loaded(struct Image** images, int id);
void draw_image(struct Image* image);
/*void update_vars(struct ChangingValue* vars, double time);*/

#endif

