#include "image.h"

struct Image* load_image(char* filename)
{
	struct Image* image = malloc(sizeof(struct Image));
	image->x = 0;
	image->y = 0;
	if(!(image->bitmap = al_load_bitmap(filename)))
		return NULL;
	else
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

