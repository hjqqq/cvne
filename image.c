#include "image.h"

struct Image* load_image(char* filename, float x, float y)
{
	struct Image* image = malloc(sizeof(struct Image));
	/*int i;*/
	if(!(image->bitmap = al_load_bitmap(filename)))
	{
		free(image);
		return NULL;
	}
	/*image->centerx = al_get_bitmap_width(image->bitmap) / 2;
	image->centery = al_get_bitmap_height(image->bitmap) / 2;
	for(i = 0; i < 5; i++)
	{
		image->vars[i].value = (i == XSCALE || i == YSCALE) ? 1.0 : 0.0;
		image->vars[i].endtime = -1.0;
	}*/
	image->x = x;
	image->y = y;
	return image;
}

void free_image(struct Image* image)
{
	al_destroy_bitmap(image->bitmap);
	free(image);
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

struct Image* image_loaded(struct Image** images, int id)
{
	struct Image* image = images[id];
	if(!image)
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
		int x, y;
		if(game->display->images[id])
		{
			x = game->display->images[id]->x;
			y = game->display->images[id]->y;
			free_image(game->display->images[id]);
		}
		else
		{
			x = 0;
			y = 0;
		}
		if(!(game->display->images[id] = load_image(filename, 0, 0)))
			sprintf(error, "cannot load image %d \"%s\"", id, filename);
	}
}

void cmd_close_image(struct Game* game, char* arg)
{
	int id = eval(game->vars, arg);
	if(image_id_in_range(id))
		if(image_loaded(game->display->images, id))
			free_image(game->display->images[id]);
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
		struct Image* image;
		if((image = image_loaded(game->display->images, id)))
		{
			image->x = x;
			image->y = y;
			if(*game->verbose)
				printf("image %s%d%s -> %s%d%s;%s%d%s",
					TGREEN, id, TDEF, TMAGENTA, x, TDEF, TMAGENTA, y, TDEF);
		}
	}
}

