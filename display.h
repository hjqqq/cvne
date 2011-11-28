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

struct Game;

struct Display
{
	ALLEGRO_DISPLAY* screen;
	struct Image** images;
	struct Sound** sounds;
	struct MessageBox* messagebox;
	ALLEGRO_FONT* font;
};

struct Display* build_display(void);
void init_display(struct Game* game);
void free_display(struct Display* display);
void display_display(struct Game* game);

void cmd_display(struct Game* game, char* arg);

#endif

