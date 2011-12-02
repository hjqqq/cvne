#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game.h"
#include "defines.h"
#include "image.h"
#include "sound.h"
#include "var.h"
#include "interface.h"
#include "color.h"

struct Game;

struct Image
{
	ALLEGRO_BITMAP* bitmap;
	float x;
	float y;
};

struct Display
{
	int* width;
	int* height;
	ALLEGRO_DISPLAY* screen;
	struct Image images[IMAGES];
	struct Sound** sounds;
	struct MessageBox* messagebox;
	int mousex;
	int mousey;
};

struct Display* build_display(void);
void init_display(struct Game* game);
void free_display(struct Display* display);
void display_display(struct Game* game);

void cmd_display(struct Game* game, char* arg);

#endif

