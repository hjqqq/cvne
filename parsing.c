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

