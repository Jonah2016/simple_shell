#include "shell.h"

/**
 * variable_expander - expand variables
 * @data: a pnt to a struct of the prog data
 *
 * Return: void, but sets errno notification.
 */
void variable_expander(application_data *data)
{
	int i, j;
	char line[BUFF_SIZE] = {0}, expansion[BUFF_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			lng_to_str(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			lng_to_str(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			tmp = env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			tmp ? buffer_add(line, tmp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_dupl(line);
	}
}

/**
 * alias_expd - expands the aliases
 * @data: a pnt to a struct of the prog data
 *
 * Return: void, but set errno.
 */
void alias_expd(application_data *data)
{
	int i, j, was_expanded = 0;
	char line[BUFF_SIZE] = {0}, expansion[BUFF_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		tmp = read_alias(data, expansion);
		if (tmp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, tmp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_dupl(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
