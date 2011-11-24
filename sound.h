#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "game.h"

struct Game;

struct Sound
{
	char name[SOUND_NAME_SIZE];
	ALLEGRO_SAMPLE* data;
	ALLEGRO_SAMPLE_ID id;
};

struct Sound* loadplay_sound(char* filename, int loop);
void freestop_sound(struct Sound* sound);
int sound_id_in_range(int id);
struct Sound* sound_loaded(struct Sound** sound, int id);

void cmd_play_sound(struct Game* game, char* arg);
void cmd_play_sound_loop(struct Game* game, char* arg);
void cmd_stop_sound(struct Game* game, char* arg);

#endif

