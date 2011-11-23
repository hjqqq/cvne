#include "parsing.h"

char* cut_command(char* buffer)
{
	char* arg;
	int i = skip_to_space(buffer, 0);
	buffer[i] = '\0';
	arg = buffer + skip_space(buffer, i + 1);
	while(buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	buffer[i] = '\0';
	i++;
	while(buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	buffer[i] = '\0';
	return arg;
}

int skip_space(char* s, int i)
{
	while(s[i] == ' ' || s[i] == '\t')
		i++;
	return i;
}

int skip_to_space(char* s, int i)
{
	while(s[i] != ' ' && s[i] != '\t' && s[i] != '\0' && s[i] != '\n')
		i++;
	return i;
}

char* strip_begin(char* s)
{
	return s + skip_space(s, 0);
}

void path_compatibilize(char* path)
{
	int i;
	for(i = 0; path[i] != '\0'; i++)
	{
#ifdef __WIN32
		if(path[i] == '/') path[i] = '\\';
#else
		if(path[i] == '\\') path[i] = '/';
#endif
	}
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

int eval(struct Item* vars, char* s)
{
	int a, b, i;
	remove_spaces(s);
	replace_vars_values(vars, s);
	if(error[0] != '\0') return 0;
	check_expr(s);
	if(error[0] != '\0') return 0;
	a = atoi(s);
	if(s[0] == '\0') return 0;
	for(i = 1; s[i] != '\0'; i++)
	{
		switch(s[i])
		{
			case '+': return a + atoi(s + i + 1);
			case '-': return a - atoi(s + i + 1);
			case '*': return a * atoi(s + i + 1);
			case '/':
				b = atoi(s + i + 1);
				if(b == 0)
				{
					sprintf(error, "division by zero");
					return 0;
				}
				return a / b;
			case '%':
				b = atoi(s + i + 1);
				if(b == 0)
				{
					sprintf(error, "modulo by zero");
					return 0;
				}
				return a % b;
		}
	}
	return a;
}

void remove_spaces(char* s)
{
	int offset = 0, i;
	for(i = 0; s[i] != '\0'; i++)
	{
		if(s[i] == ' ' || s[i] == '\t')
			offset++;
		s[i] = s[i + offset];
	}
	s[i] = '\0';
}

void check_expr(char* s)
{
	int i;
	for(i = 0; s[i] != '\0'; i++)
	{
		if(s[i] != '0' && (s[i] < '1' || s[i] > '9') && s[i] != '%' &&
			s[i] != '*' && s[i] != '+' && s[i] != '/' && s[i] != '-' && s[i] != '/')
		{
			sprintf(error, "invalid char in expr \"%s\" at pos %d : \'%c\'", s, i, s[i]);
			break;
		}
	}
}

