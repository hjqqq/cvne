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

struct MessageBox* init_messagebox(void)
{
	struct MessageBox* messagebox = malloc(sizeof(struct MessageBox));
	int i;
	messagebox->font = al_load_ttf_font(FONT_FILE, DEFAULT_FONT_SIZE, 0);
	if(!messagebox->font)
	{
		sprintf(error, "cannot load font file \"%s\"", FONT_FILE);
		free(messagebox);
		return NULL;
	}
	messagebox->image = -1;
	messagebox->lineheight = al_get_font_line_height(messagebox->font);
	messagebox->display = 0;
	messagebox->lines = NULL;
	messagebox->i = 0;
	messagebox->colors = calloc(COLORS, sizeof(struct Color));
	for(i = 0; i < COLORS; i++)
		messagebox->colors[i] = al_map_rgba(0, 0, 0, 0);
	return messagebox;
}

void free_messagebox(struct MessageBox* messagebox)
{
	free(messagebox->colors);
	al_destroy_font(messagebox->font);
	empty_lines(messagebox);
	free(messagebox);
}

void add_line(struct MessageBox* messagebox, char* text, char* target)
{
	struct Line* line = malloc(sizeof(struct Line));
	ALLEGRO_COLOR fgcolor, bgcolor;
	if(target)
	{
		fgcolor = get_color_var(messagebox->colors,
			*messagebox->choice_color, al_map_rgba(0, 0, 0, 255));
		bgcolor = get_color_var(messagebox->colors,
			*messagebox->choice_bg_color, al_map_rgba(0, 0, 0, 0));
		strcpy(line->target, target);
	}
	else
	{
		fgcolor = get_color_var(messagebox->colors,
			*messagebox->message_color, al_map_rgba(255, 0, 0, 255));
		bgcolor = get_color_var(messagebox->colors,
			*messagebox->message_bg_color, al_map_rgba(255, 255, 255, 127));
		line->target[0] = '\0';
	}
	line->pos = messagebox->i;
	messagebox->i++;
	line->width = al_get_text_width(messagebox->font, text);
	line->bitmap = al_create_bitmap(line->width, messagebox->lineheight);
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
	if(!game->wait)
		cmd_clear_lines(game, "");
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
	add_line(game->display->messagebox, s, NULL);
}

void cmd_show_message(struct Game* game, char* s)
{
	game->display->messagebox->display = 1;
	game->wait = waitforinput;
}

void cmd_clear_lines(struct Game* game, char* s)
{
	empty_lines(game->display->messagebox);
}

