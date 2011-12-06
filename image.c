#include "image.h"

int load_image(struct Image* image, char* filename)
{
	return (image->bitmap = al_load_bitmap(filename)) ? 1 : 0;
}

int image_id_in_range(int id)
{
	if(id < 0 || id >= IMAGES)
	{
		sprintf(error, "image id %d not in range [0,%d]", id, IMAGES - 1);
		return 0;
	}
	else
		return 1;
}

struct Image* image_loaded(struct Image* images, int id)
{
	struct Image* image = &images[id];
	if(!image->bitmap)
		sprintf(error, "image %d is not loaded", id);
	return image;
}

void draw_image(struct Image* image)
{
	al_draw_bitmap(image->bitmap, image->x, image->y, 0);
}

void cmd_load_image(struct Game* game, char* arg)
{
	char* filename = cut_command(arg);
	int id = eval(game->vars, arg);
	path_compatibilize(filename);
	if(image_id_in_range(id))
	{
		if(game->display->images[id].bitmap)
		{
			al_destroy_bitmap(game->display->images[id].bitmap);
			game->display->images[id].bitmap = NULL;
		}
		if(!load_image(game->display->images + id, filename))
			sprintf(error, "cannot load image %d \"%s\"", id, filename);
	}
}

void cmd_close_image(struct Game* game, char* arg)
{
	int id = eval(game->vars, arg);
	if(image_id_in_range(id))
	{
		if(image_loaded(game->display->images, id)->bitmap)
		{
			al_destroy_bitmap(game->display->images[id].bitmap);
			game->display->images[id].bitmap = NULL;
		}
	}
}

void cmd_move_image(struct Game* game, char* arg)
{
	int id, x, y;
	char* cur = cut_command(arg);
	id = eval(game->vars, arg);
	arg = cut_command(cur);
	y = eval(game->vars, arg);
	x = eval(game->vars, cur);
	if(image_id_in_range(id))
	{
		game->display->images[id].x = x;
		game->display->images[id].y = y;
		if(*game->verbose)
			printf("image %s%d%s -> %s%d%s;%s%d%s",
				TGREEN, id, TDEF, TMAGENTA, x, TDEF, TMAGENTA, y, TDEF);
		printf("printf at %f;%f\n", game->display->images[id].x, game->display->images[id].y);
	}
}

