#include "sound.h"

struct Sound* loadplay_sound(char* filename, int loop)
{
	struct Sound* sound = malloc(sizeof(struct Sound));
	if(!(sound->data = al_load_sample(filename)))
	{
		free(sound);
		return NULL;
	}
	if(!al_play_sample(sound->data, 1.0, 0.0, 1.0, 
		loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE, &(sound->id)))
	{
		al_destroy_sample(sound->data);
		free(sound);
		return NULL;
	}
	return sound;
}

void freestop_sound(struct Sound* sound)
{
	al_stop_sample(&(sound->id));
	al_destroy_sample(sound->data);
	free(sound);
}

int sound_id_in_range(int id)
{
	if(id < 0 && id >= SOUNDS)
	{
		sprintf(error, "sound id %d not in range [0,%d]", id, SOUNDS - 1);
		return 0;
	}
	else
		return 1;
}

struct Sound* sound_loaded(struct Sound** sounds, int id)
{
	struct Sound* sound = sounds[id];
	if(!sound)
		sprintf(error, "sound %d is not loaded", id);
	return sound;
}

void cmd_play_sound(struct Game* game, char* arg)
{
	char* filename = cut_command(arg);
	int id = eval(game->vars, arg);
	path_compatibilize(filename);
	if(sound_id_in_range(id))
	{
		if(game->display->sounds[id])
			freestop_sound(game->display->sounds[id]);
		if(!(game->display->sounds[id] = loadplay_sound(filename, 0)))
			sprintf(error, "cannot load sound %d \"%s\"", id, filename);
	}
}

void cmd_play_sound_loop(struct Game* game, char* arg)
{
	char* filename = cut_command(arg);
	int id = eval(game->vars, arg);
	path_compatibilize(filename);
	if(sound_id_in_range(id))
	{
		if(game->display->sounds[id])
			freestop_sound(game->display->sounds[id]);
		if(!(game->display->sounds[id] = loadplay_sound(filename, 1)))
			sprintf(error, "cannot load sound %d \"%s\"", id, filename);
	}
}

void cmd_stop_sound(struct Game* game, char* arg)
{
	int id = eval(game->vars, arg);
	struct Sound* sound;
	if(sound_id_in_range(id))
	{
		if((sound = sound_loaded(game->display->sounds, id)))
		{
			freestop_sound(sound);
			game->display->sounds[id] = NULL;
		}
	}		
}

