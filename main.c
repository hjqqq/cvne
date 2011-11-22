#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game.h"

int main(int argc, char** argv)
{
	printf("CVNE running, built on %s at %s.\n", __DATE__, __TIME__);
	if(!al_init() || !al_init_image_addon())
		return EXIT_FAILURE;
	if(argc > 1)
		run_game(argv[1]);
	else
		run_game("main");
	al_shutdown_image_addon();
	return EXIT_SUCCESS;
}

