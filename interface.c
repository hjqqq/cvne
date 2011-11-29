#include "interface.h"

int coord_in_choice(int x, int y, struct Line* line)
{
	if(line->target[0] == '\0')
		return 0;
	else
		return x >= line->messagebox->x &&
			y >= line->messagebox->y + line->messagebox->lineheight * line->pos &&
			x < line->messagebox->x + line->width &&
			y < line->messagebox->y + line->messagebox->lineheight * (line->pos + 1);
}

struct MessageBox* init_messagebox(ALLEGRO_FONT* font)
{
	struct MessageBox* messagebox = malloc(sizeof(struct MessageBox));
	messagebox->image = -1;
	messagebox->x = 0;
	messagebox->y = 0;
	messagebox->lineheight = al_get_font_line_height(font);
	messagebox->display = 0;
	messagebox->lines = NULL;
	messagebox->i = 0;
	return messagebox;
}

void free_messagebox(struct MessageBox* messagebox)
{
	free_list(messagebox->lines, free);
	free(messagebox);
}

void add_message(struct Display* display, char* text)
{
	struct Line* line = malloc(sizeof(struct Line));
	strcpy(line->text, text);
	line->target[0] = '\0';
	line->pos = display->messagebox->i;
	display->messagebox->i++;
	line->width = al_get_text_width(display->font, text);
	if(display->messagebox->lines)
		add_after((void*) line, display->messagebox->lines);
	else
		display->messagebox->lines = build_first_item((void*) line);
}

void free_line(void* ptr)
{
	struct Line* line = (struct Line*) ptr;
	free(line);
}

void empty_lines(struct MessageBox* messagebox)
{
	free_list(messagebox->lines, free_line);
	messagebox->lines = NULL;
}

void waitforinput(struct Game* game, ALLEGRO_EVENT* event)
{
	if(event)
	{
		switch(event->type)
		{
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: game->wait = NULL;
			case ALLEGRO_EVENT_KEY_DOWN: game->wait = NULL;
		}
	}
}

void waitforchoice(struct Game* game, ALLEGRO_EVENT* event)
{
	if(event)
	{
		if(event->type == ALLEGRO_EVENT_KEY_DOWN || event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			struct Item* cur = game->display->messagebox->lines;
			while(cur)
			{
				if(coord_in_choice(event->mouse.x, event->mouse.y, cur->val))
					game->wait = 0;
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

void cmd_message(struct Game* game, char* s)
{
	add_message(game->display, s);
}

void cmd_show_message(struct Game* game, char* s)
{
	game->display->messagebox->display = 1;
	game->wait = waitforinput;
}

