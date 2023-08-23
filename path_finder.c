#include "shell.h"

int file_checker(char *full_path);

/**
 * application_finder - find a prog in path
 * @data: a pnt to the prog data
 * Return: 0 if success, errcode otherwise
 */

int application_finder(application_data *data)
{
	int i = 0, resp_code = 0;
	char **dirs;

	if (!data->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (file_checker(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concatination(str_dupl("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dirs = make_token_path(data); /* search in the PATH */

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{ /* appends the function_name to path */
		dirs[i] = str_concatination(dirs[i], data->tokens[0]);
		resp_code = file_checker(dirs[i]);
		if (resp_code == 0 || resp_code == 126)
		{ /* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_dupl(dirs[i]);
			array_pnts_freer(dirs);
			return (resp_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	array_pnts_freer(dirs);
	return (resp_code);
}

/**
 * make_token_path - make_token the path in dirs
 * @data: a pointer to the program's data
 * Return: array of path dirs
 */

char **make_token_path(application_data *data)
{
	int i = 0;
	int counter_dirs = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{ /*path not found*/
		return (NULL);
	}

	PATH = str_dupl(PATH);

	/* find the number of dirs in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_dirs++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_dirs);

	/*make_token and duplicate each token of path*/
	i = 0;
	tokens[i] = str_dupl(_strtokenize(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_dupl(_strtokenize(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * file_checker - checks if exists a file, if it is not a dir and
 * if it has excecution permisions.
 * @full_path: pnt to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int file_checker(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
