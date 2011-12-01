#include "messagebox.h"

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

