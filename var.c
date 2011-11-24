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

void set_var(struct Item* list, char* name, int value)
{
	struct Var* var = get_var(list, name);
	if(!var)
	{
		var = malloc(sizeof(struct Var));
		strcpy(var->name, name);
		add_after(list, var);
	}
	var->value = value;
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

void cmd_set(struct Game* game, char* arg)
{
	char* valuestr = cut_command(arg);
	int value = eval(game->vars, valuestr);
	if(*game->verbose)
		printf("%s%s%s = %s%d%s", TGREEN, arg, TDEF, TMAGENTA, value, TDEF);
	set_var(game->vars, arg, value);
}

