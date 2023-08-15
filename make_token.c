#include "shell.h"
/**
 * make_token - this func separate a str using a designed delimiter
 * @data: a pointer to the prog data
 * Return: an array of the diff parts of a str
 */
void make_token(application_data *data)
{
	char *delimit = " \t";
	int i, j, counter = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimit[j]; j++)
		{
			if (data->input_line[i] == delimit[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->application_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_dupl(_strtokenize(data->input_line, delimit));
	data->command_name = str_dupl(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_dupl(_strtokenize(NULL, delimit));
	}
}
