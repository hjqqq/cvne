#include "image.h"

struct Image* load_image(char* filename, float x, float y)
{
	struct Image* image = malloc(sizeof(struct Image));
	/*int i;*/
	if(!(image->bitmap = al_load_bitmap(filename)))
		return NULL;
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

int image_loaded(struct Image** images, int id)
{
	if(images[id])
		return 1;
	else
	{
		sprintf(error, "image %d is not loaded", id);
		return 0;
	}
}

void draw_image(struct Image* image)
{
	al_draw_bitmap(image->bitmap, image->x, image->y, 0);
}

/*void update_vars(struct ChangingValue* vars, double time)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		if(time > vars[i].endtime)
			vars[i].value = vars[i].endvalue;
		else
			vars[i].value = vars[i].startvalue + 
				(vars[i].endvalue - vars[i].startvalue) /
				(vars[i].endtime - vars[i].starttime);
	}
}*/

