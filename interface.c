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
	messagebox->lineheight = al_get_font_line_height(messagebox->font);
	messagebox->display = 0;
	messagebox->lines = NULL;
	messagebox->i = 0;
	for(i = 0; i < COLORS; i++)
		messagebox->colors[i] = al_map_rgba(0, 0, 0, 0);
	return messagebox;
}

void free_messagebox(struct MessageBox* messagebox)
{
	al_destroy_font(messagebox->font);
	empty_lines(messagebox);
	free(messagebox);
}

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

void cmd_clear_lines(struct Game* game, char* s)
{
	empty_lines(game->display->messagebox);
}

void cmd_set_font(struct Game* game, char* s)
{
	char* filename = cut_command(s);
	if(game->display->messagebox->font)
		al_destroy_font(game->display->messagebox->font);
	game->display->messagebox->font = al_load_ttf_font(filename, eval(game->vars, s), 0);
	if(!game->display->messagebox->font)
		sprintf(error, "cannot load font file \"%s\"", filename);
	else
		game->display->messagebox->lineheight = al_get_font_line_height(
			game->display->messagebox->font);
}

void cmd_set_color(struct Game* game, char* s)
{
	char *r, *g, *b, *a;
	int id;
	r = cut_command(s);
	g = cut_command(r);
	b = cut_command(g);
	a = cut_command(b);
	id = eval(game->vars, s);
	if(id < 0 || id >= COLORS)
		sprintf(error, "color id out of range : %d", id);
	else
		game->display->messagebox->colors[id] = 
			al_map_rgba(eval(game->vars, r), eval(game->vars, g),
			eval(game->vars, b), eval(game->vars, a));
}

