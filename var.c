#include "var.h"

struct Var* get_var(struct Item* list, char* name)
{
	while(list)
	{
		if(strcmp(((struct Var*)list->val)->name, name) == 0)
			return (struct Var*)list->val;
		list = list->next;
	}
	return NULL;
}

int get_var_value(struct Item* list, char* name, int default_value)
{
	struct Var* var = get_var(list, name);
	return var ? var->value : default_value;
}

struct Var* set_var(struct Item* list, char* name, int value)
{
	struct Var* var = get_var(list, name);
	if(!var)
	{
		var = malloc(sizeof(struct Var));
		strcpy(var->name, name);
		add_after(list, var);
	}
	var->value = value;
	return var;
}

void replace_vars_values(struct Item* vars, char* s)
{
	int i, j = 0, k = 0;
	char newstring[BUFFER_SIZE];
	for(i = 0; s[i] != '\0'; i++)
	{
		char varname[VAR_NAME_SIZE] = {'\0'};
		while(((s[i] >= 'a' && s[i] <= 'z') ||
			(s[i] >= 'A' && s[i] <= 'Z') ||
			s[i] == '_') && j < VAR_NAME_SIZE - 1)
		{
			varname[k] = s[i];
			k++; i++;
		}
		if(varname[0] != '\0')
		{
			struct Var* var;
			varname[k] = '\0';
			var = get_var(vars, varname);
			if(var)
			{
				sprintf(newstring + j, "%d", var->value);
				j += strlen(newstring + j);
			}
			else
			{
				sprintf(error, "unknown var \"%s\"", varname);
				break;
			}
			k = 0;
		}
		newstring[j] = s[i];
		j++;
	}
	newstring[j] = '\0';
	strcpy(s, newstring);
}

int* setbind(struct Item* list, char* name, int value)
{
	return &(set_var(list, name, value)->value);
}

struct Item* build_special_vars(struct Game* game)
{
	struct Var* firstvar = malloc(sizeof(struct Var));
	struct Item* list;
	strcpy(firstvar->name, "null");
	firstvar->value = 0;
	list = build_first_item(firstvar);
	game->display->width = setbind(list, "_width", 640);
	game->display->height = setbind(list, "_height", 480);
	game->verbose = setbind(list, "_verbose", 1);
	game->display->messagebox->message_color = setbind(list, "_message_color", -1);
	game->display->messagebox->choice_color = setbind(list, "_choice_color", -1);
	game->display->messagebox->message_bg_color = setbind(list, "_message_bg_color", -1);
	game->display->messagebox->choice_bg_color = setbind(list, "_choice_bg_color", -1);
	game->display->messagebox->x = setbind(list, "_messagebox_x", 0);
	game->display->messagebox->y = setbind(list, "_messagebox_y", 0);
	return list;
}

ALLEGRO_COLOR get_color_var(ALLEGRO_COLOR* colors, int id, ALLEGRO_COLOR defaultval)
{
	if(id < 0 || id >= COLORS)
		return defaultval;
	else
		return colors[id];
}

void cmd_set(struct Game* game, char* arg)
{
	char* valuestr = cut_command(arg);
	int value = eval(game->vars, valuestr);
	if(*game->verbose)
		printf("%s%s%s = %s%d%s", TGREEN, arg, TDEF, TMAGENTA, value, TDEF);
	set_var(game->vars, arg, value);
}

