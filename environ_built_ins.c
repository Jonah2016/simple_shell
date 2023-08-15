#include "shell.h"

/**
 * environ_built_in - display the env where the shell is executed
 * @data: struct for the prog data
 * Return: 0 if successful, or another num if declared in the args
 */
int environ_built_in(application_data *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *cp_var = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{ /* checks if exists a char = */
			if (data->tokens[1][i] == '=')
			{ /* checks if a var exist with the same name and change val*/
				/* temporal */
				cp_var = str_dupl(env_get_key(cpname, data));
				if (cp_var != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);

				/* print the env */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{ /* print the var if doesnt exist in the env */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{ /* return old value of the var*/
					env_set_key(cpname, cp_var, data);
					free(cp_var);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * list_built_insset_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int list_built_insset_env(application_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * list_built_insunset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int list_built_insunset_env(application_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}

