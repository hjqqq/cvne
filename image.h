#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"
#include "defines.h"
#include "display.h"
#include "image.h"

struct Image;
struct Game;

int load_image(struct Image* image, char* filename);
int image_id_in_range(int id);
struct Image* image_loaded(struct Image* images, int id);
void draw_image(struct Image* image);

void cmd_load_image(struct Game* game, char* arg);
void cmd_close_image(struct Game* game, char* arg);
void cmd_move_image(struct Game* game, char* arg);

#endif

