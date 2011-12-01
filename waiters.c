#include "waiters.h"

void waitforchoice(struct Game* game, ALLEGRO_EVENT* event)
{
	if(event)
	{
		if(event->type == ALLEGRO_EVENT_KEY_DOWN || event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			struct Item* cur = game->display->messagebox->lines;
			while(cur)
			{
				struct Line* line = (struct Line*) cur->val;
				if(coord_in_choice(event->mouse.x, event->mouse.y, line))
				{
					cmd_go(game, line->target);
					break;
				}
				cur = cur->next;
			}
			game->wait = 0;
			empty_lines(game->display->messagebox);
		}
	}
}

void waitforforcedchoice(struct Game* game, ALLEGRO_EVENT* event)
{
	if(event)
	{
		if(event->type == ALLEGRO_EVENT_KEY_DOWN || event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			struct Item* cur = game->display->messagebox->lines;
			while(cur)
			{
				struct Line* line = (struct Line*) cur->val;
				if(coord_in_choice(event->mouse.x, event->mouse.y, line))
				{
					cmd_go(game, line->target);
					game->wait = 0;
					empty_lines(game->display->messagebox);
					break;
				}
				cur = cur->next;
			}
		}
	}
}

void waitfortime(struct Game* game, ALLEGRO_EVENT* event)
{
	if(al_get_time() > game->wait_time)
		game->wait = NULL;
}

