#ifndef WAITERS_H_INCLUDED
#define WAITERS_H_INCLUDED

#include <allegro5/allegro.h>

#include "game.h"

void waitforchoice(struct Game* game, ALLEGRO_EVENT* event);
void waitforforcedchoice(struct Game* game, ALLEGRO_EVENT* event);
void waitfortime(struct Game* game, ALLEGRO_EVENT* event);

#endif

