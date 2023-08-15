#include "shell.h"

/**
 * built_in_exit - exit the program with a status
 * @data: get struct for the program data
 * Return: 0 if successful, or other num if it declared in args
 */
int built_in_exit(application_data *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{ /*if exists arg for exit, check if is a number*/
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
					&& data->tokens[1][i] != '+')
			{ /*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	all_data_freer(data);
	exit(errno);
}

/**
 * built_in_cd - change the curr dir
 * @data: struct for the program's data
 * Return: 0 if success, or other num if its declared in the args
 */
int built_in_cd(application_data *data)
{
	char *home_directory = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_wrkn_dir(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_wrkn_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_directory)
			home_directory = getcwd(old_dir, 128);

		return (set_wrkn_dir(data, home_directory));
	}
	return (0);
}

/**
 * set_wrkn_dir - set the working dir
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: 0 if successful, or other num if declared in the args
 */
int set_wrkn_dir(application_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * list_built_inshelp - shows the env where the shell runs
 * @data: struct for the prog data
 * Return: 0 if sucessfull, or other num if its declared in the args
 */
int list_built_inshelp(application_data *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MESSAGE;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = EXIT_HELP_MESSAGE;
	mensajes[2] = ENV_HELP_MESSAGE;
	mensajes[3] = SET_ENV_HELP_MESSAGE;
	mensajes[4] = UNSET_ENV_HELP_MESSAGE;
	mensajes[5] = CD_HELP_MESSAGE;

	for (i = 0; mensajes[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[i], length))
		{
			_print(mensajes[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 response */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * built_in_alias - add, remove or show all the aliases
 * @data: struct for the prog data
 * Return: 0 if successful, or another num if declared in the args
 */
int built_in_alias(application_data *data)
{
	int i = 0;

	/* if there are no args, print all env variables */
	if (data->tokens[1] == NULL)
		return (alias_print_errr(data, NULL));

	while (data->tokens[++i])
	{ /* if args are present, set or print each env var*/
		if (chars_counter(data->tokens[i], "="))
			write_alias(data->tokens[i], data);
		else
			alias_print_errr(data, data->tokens[i]);
	}

	return (0);
}

