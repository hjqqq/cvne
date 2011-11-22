#include <stdlib.h>
#include <stdio.h>

#include "game.h"

int main(void)
{
	printf("CVNE running, built on %s at %s.\n", __DATE__, __TIME__);
	run_game("main");
	return EXIT_SUCCESS;
}

