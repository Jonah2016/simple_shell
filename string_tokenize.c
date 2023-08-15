#include "shell.h"
/**
 * _strtokenize - separates strs with delimits
 * @line: It\u00b4s pnt to arr we received from getline.
 * @delim: Its chars we mark off str in parts.
 * Return: A pnt to the created token
 */
char *_strtokenize(char *line, char *delim)
{
	int j;
	static char *str;
	char *cp_str;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}
		if (delim[j] == '\0')
			break;
	}
	cp_str = str;
	if (*cp_str == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (cp_str);
			}
		}
	}
	return (cp_str);
}
