#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "game.h"

int main(int argc, char** argv)
{
	printf("%sCVNE%s running, built on %s%s%s at %s%s%s.\n",
		TYELLOW, TDEF, TRED, __DATE__, TDEF, TRED, __TIME__, TDEF);
	if(sizeof(struct Color) > sizeof(int))
	{
		fprintf(stderr, "Error : cannot store a struct Color in an int on this system. Exiting.\n");
		return EXIT_FAILURE;
	}
	if(!al_init() ||
		!al_init_image_addon() ||
		!al_install_mouse() ||
		!al_install_audio() ||
		!al_init_acodec_addon() ||
		!al_init_ttf_addon() ||
		!al_reserve_samples(SOUNDS))
		return EXIT_FAILURE;
	al_init_font_addon();
	if(argc > 1)
		run_game(argv[1]);
	else
		run_game("main");
	al_shutdown_image_addon();
	return EXIT_SUCCESS;
}

