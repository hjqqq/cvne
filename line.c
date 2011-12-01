#include "line.h"

void add_line(struct MessageBox* messagebox, char* text, char* target)
{
	struct Line* line = malloc(sizeof(struct Line));
	ALLEGRO_COLOR fgcolor, bgcolor;
	if(target == NULL)
	{
		fgcolor = get_color_var(messagebox->colors,
			*messagebox->message_color, al_map_rgba(0, 255, 255, 255));
		bgcolor = get_color_var(messagebox->colors,
			*messagebox->message_bg_color, al_map_rgba(0, 0, 0, 0));
		line->target[0] = '\0';
	}
	else
	{
		fgcolor = get_color_var(messagebox->colors,
			*messagebox->choice_color, al_map_rgba(255, 0, 0, 255));
		bgcolor = get_color_var(messagebox->colors,
			*messagebox->choice_bg_color, al_map_rgba(255, 255, 255, 127));
		strcpy(line->target, target);
	}
	line->pos = messagebox->i;
	messagebox->i++;
	line->width = al_get_text_width(messagebox->font, text);
	line->bitmap = al_create_bitmap(line->width, messagebox->lineheight);
	line->messagebox = messagebox;
	al_set_target_bitmap(line->bitmap);
	al_clear_to_color(bgcolor);
	al_draw_text(messagebox->font, fgcolor, 0, 0, 0, text);
	if(messagebox->lines)
		add_after(messagebox->lines, (void*) line);
	else
		messagebox->lines = build_first_item((void*) line);
}

void free_line(void* ptr)
{
	struct Line* line = (struct Line*) ptr;
	al_destroy_bitmap(line->bitmap);
	free(line);
}

void empty_lines(struct MessageBox* messagebox)
{
	if(messagebox->lines)
		free_list(messagebox->lines, free_line);
	messagebox->lines = NULL;
	messagebox->i = 0;
}

void cmd_clear_lines(struct Game* game, char* s)
{
	empty_lines(game->display->messagebox);
}

