#include "shell.h"

/**
 * _getline - read 1 line from the prompt.
 * @data: struct for the prog data
 *
 * Return: read counted bytes.
 */
int _getline(application_data *data)
{
	char buff[BUFF_SIZE] = {'\0'};
	static char *arr_commands[10] = {NULL};
	static char arr_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* check if doesnt exist more commands in the array */
	if (!arr_commands[0] || (arr_operators[0] == '&' && errno != 0) ||
		(arr_operators[0] == '|' && errno == 0))
	{
		/*free the allocated memo of the array if it exist */
		for (i = 0; arr_commands[i]; i++)
		{
			free(arr_commands[i]);
			arr_commands[i] = NULL;
		}

		/* read from the file descript int to buff */
		bytes_read = read(data->file_descriptor, &buff, BUFF_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		i = 0;
		do {
			arr_commands[i] = str_dupl(_strtokenize(i ? NULL : buff, "\n;"));
			/*validate and split for && and || operators*/
			i = check_logic_ops(arr_commands, i, arr_operators);
		} while (arr_commands[i++]);
	}

	/*gets the next (command 0) and remove it for the array*/
	data->input_line = arr_commands[0];
	for (i = 0; arr_commands[i]; i++)
	{
		arr_commands[i] = arr_commands[i + 1];
		arr_operators[i] = arr_operators[i + 1];
	}

	return (str_length(data->input_line));
}

/**
 * check_logic_ops - checks and split for && and || operators
 * @arr_commands: array of the commands.
 * @i: index in the arr_commands to be checked
 * @arr_operators: arr of the logical ops for each previous command
 *
 * Return: index of the last command in the arr_commands.
 */
int check_logic_ops(char *arr_commands[], int i, char arr_operators[])
{
	char *temp = NULL;
	int j;

	/* check for the & char in the command line*/
	for (j = 0; arr_commands[i] != NULL && arr_commands[i][j]; j++)
	{
		if (arr_commands[i][j] == '&' && arr_commands[i][j + 1] == '&')
		{
			/* split line if chars && is found */
			temp = arr_commands[i];
			arr_commands[i][j] = '\0';
			arr_commands[i] = str_dupl(arr_commands[i]);
			arr_commands[i + 1] = str_dupl(temp + j + 2);
			i++;
			arr_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (arr_commands[i][j] == '|' && arr_commands[i][j + 1] == '|')
		{
			/* split line if chars || is found */
			temp = arr_commands[i];
			arr_commands[i][j] = '\0';
			arr_commands[i] = str_dupl(arr_commands[i]);
			arr_commands[i + 1] = str_dupl(temp + j + 2);
			i++;
			arr_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
