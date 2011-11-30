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
	/*char text[MESSAGE_LINE_SIZE];*/
	ALLEGRO_BITMAP* bitmap;
	struct MessageBox* messagebox;
};

struct MessageBox
{
	ALLEGRO_COLOR colors[COLORS];
	int* image;
	int* x;
	int* y;
	int i;
	struct Item* lines;
	int display;
	int lineheight;
	int* message_color;
	int* choice_color;
	int* message_bg_color;
	int* choice_bg_color;
	ALLEGRO_FONT* font;
};

int coord_in_choice(int x, int y, struct Line* line);
struct MessageBox* init_messagebox(void);
void free_messagebox(struct MessageBox* messagebox);
void add_line(struct MessageBox* messagebox, char* text, char* target);
void free_line(void* ptr);
void empty_lines(struct MessageBox* messagebox);

void waitforchoice(struct Game* game, ALLEGRO_EVENT* event);
void waitforforcedchoice(struct Game* game, ALLEGRO_EVENT* event);
void waitfortime(struct Game* game, ALLEGRO_EVENT* event);

void cmd_message(struct Game* game, char* arg);
void cmd_choice(struct Game* game, char* arg);
void cmd_show_message(struct Game* game, char* arg);
void cmd_force_choice(struct Game* game, char* arg);
void cmd_clear_lines(struct Game* game, char* arg);
void cmd_set_font(struct Game* game, char* arg);
void cmd_set_color(struct Game* game, char* arg);

#endif

