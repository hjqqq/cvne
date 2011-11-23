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

void replace_v_vars(int* vars, char* s)
{
	int i, j = 0;
	char newstring[BUFFER_SIZE];
	for(i = 0; s[i] != '\0'; i++)
	{
		if(s[i] == 'v' && s[i + 1] == '_')
		{
			int id = atoi(s + i + 2);
			if(var_id_in_range(id))
			{
				sprintf(newstring + j, "%d", vars[id]);
				i+=2;
				while(s[i] == '0' || (s[i] >= '1' && s[i] <= '9'))
					i++;
				while(newstring[j] != '\0')
					j++;
			}
		}
		newstring[j] = s[i];
		j++;
	}
	printf("\"%s\" -> \"%s\"\n", s, newstring);
	strcpy(newstring, s);
}

