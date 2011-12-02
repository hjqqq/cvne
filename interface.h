#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "display.h"
#include "messagebox.h"
#include "line.h"
#include "waiters.h"
#include "image.h"

struct MessageBox;
struct Line;
struct Display;
struct Image;

int coord_in_choice(int x, int y, struct Line* line);
void draw_cursor(struct Image* image, struct Display* display);

void cmd_message(struct Game* game, char* arg);
void cmd_choice(struct Game* game, char* arg);
void cmd_show_message(struct Game* game, char* arg);
void cmd_force_choice(struct Game* game, char* arg);

#endif

