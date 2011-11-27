#include "interface.h"

int coord_in_choice(int x, int y, struct Choice* choice)
{
	return (x >= choice->x) && (y >= choice->y)
		&& (x < choice->x + choice->messagebox->choicewidth)
		&& (y < choice->y + choice->messagebox->choiceheight);
}

struct MessageBox* init_message_box(int dwidth, int dheight)
{
	struct MessageBox* messagebox = malloc(sizeof(struct MessageBox));
	messagebox->image = -1;
	messagebox->choiceimage = -1;
	messagebox->x = 0;
	messagebox->y = 0;
	messagebox->choicewidth = 0;
	messagebox->choiceheight = 0;
	return messagebox;
}

void free_message_box(struct MessageBox* messagebox)
{
	free(messagebox);
}

void waitforinput(struct Game* game, ALLEGRO_EVENT* event)
{
	switch(event->type)
	{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: game->waiting = 0;
		case ALLEGRO_EVENT_KEY_DOWN: game->waiting = 0;
	}
}

void waitforchoice(struct Game* game, ALLEGRO_EVENT* event)
{
	if(event->type == ALLEGRO_EVENT_KEY_DOWN || event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		int i;
		for(i = 0; i < MESSAGE_LINES; i++)
		{
			if(game->display->messagebox->choices[i])
			{
				if(coord_in_choice(event->mouse.x, event->mouse.y, game->display->messagebox->choices[i]))
				{
					cmd_go(game, game->display->messagebox->choices[i]->target);
					game->waiting = 0;
				}
			}
		}
	}
}

