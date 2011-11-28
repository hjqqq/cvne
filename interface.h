#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "game.h"
#include "display.h"

struct Display;

struct Line
{
	int pos;
	int width;
	char target[PATH_SIZE];
	char text[MESSAGE_LINE_SIZE];
	struct MessageBox* messagebox;
};

struct MessageBox
{
	int image;
	float x;
	float y;
	int i;
	struct Item* lines;
	int display;
	int lineheight;
};

int coord_in_choice(int x, int y, struct Line* line);
struct MessageBox* init_messagebox(ALLEGRO_FONT* font, int dwidth, int dheight);
void free_messagebox(struct MessageBox* messagebox);
void add_message(struct Display* display, char* text);
void free_line(void* ptr);
void empty_lines(struct MessageBox* messagebox);

void waitforinput(struct Game* game, ALLEGRO_EVENT* event);
void waitforchoice(struct Game* game, ALLEGRO_EVENT* event);
void waitfortime(struct Game* game, ALLEGRO_EVENT* event);

void cmd_message(struct Game* game, char* arg);
void cmd_show_message(struct Game* game, char* arg);

#endif

