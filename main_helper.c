#include "shell.h"

/**
 * recurr_data_freer - free the fields needed for the loop
 * @data: struct of the prog data
 * Return: void
 */
void recurr_data_freer(application_data *data)
{
	if (data->tokens)
		array_pnts_freer(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * all_data_freer - free the fields in the data
 * @data: struct of the prog data
 * Return: void
 */
void all_data_freer(application_data *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->application_name);
	}
	recurr_data_freer(data);
	array_pnts_freer(data->env);
	array_pnts_freer(data->alias_list);
}

/**
 * array_pnts_freer - this will free each pnt of an array of
 * pnts and the arr included
 * @array: arr of pnts
 * Return: void
 */
void array_pnts_freer(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
