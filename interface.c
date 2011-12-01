#include "interface.h"

int coord_in_choice(int x, int y, struct Line* line)
{
	if(line->target[0] == '\0')
		return 0;
	else
		return x >= *line->messagebox->x &&
			y >= *line->messagebox->y + line->messagebox->lineheight * line->pos &&
			x < *line->messagebox->x + line->width &&
			y < *line->messagebox->y + line->messagebox->lineheight * (line->pos + 1);
}

void draw_cursor(struct Image* image, struct Display* display)
{
	struct MessageBox* messagebox = display->messagebox;
	struct Item* cur = messagebox->lines;
	while(cur)
	{
		struct Line* line = cur->val;
		if(coord_in_choice(display->mousex, display->mousey, line))
		{
			al_draw_bitmap(image->bitmap, image->x, image->y + line->pos * messagebox->lineheight, 0);
			break;
		}
		cur = cur->next;
	}
}

void cmd_message(struct Game* game, char* s)
{
	add_line(game->display->messagebox, s, NULL);
}

void cmd_choice(struct Game* game, char* s)
{
	char* text = cut_command(s);
	add_line(game->display->messagebox, text, s);
}

void cmd_show_message(struct Game* game, char* s)
{
	game->display->messagebox->display = 1;
	game->wait = waitforchoice;
}

void cmd_force_choice(struct Game* game, char* s)
{
	game->display->messagebox->display = 1;
	game->wait = waitforforcedchoice;
}

