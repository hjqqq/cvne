#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "game.h"
#include "display.h"

struct Choice
{
	char text[MESSAGE_LINE_SIZE];
	char target[PATH_SIZE];
	float x;
	float y;
	struct MessageBox* messagebox;
};

struct MessageBox
{
	int image;
	int choiceimage;
	float x;
	float y;
	float choicewidth;
	float choiceheight;
	char lines[MESSAGE_LINES][MESSAGE_LINE_SIZE];
	struct Choice (*choices)[MESSAGE_LINES];
};

int coord_in_choice(int x, int y, struct Choice* choice);
struct MessageBox* init_message_box(int dwidth, int dheight);
void free_message_box(struct MessageBox* messagebox);

void waitforinput(struct Game* game, ALLEGRO_EVENT* event);
void waitforchoice(struct Game* game, ALLEGRO_EVENT* event);

void cmd_message(struct Game* game, char* arg);

#endif

