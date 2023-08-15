#include "shell.h"

/**
 * list_built_ins - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int list_built_ins(application_data *data)
{
	int i;
	built_ins options[] = {
		{"exit", built_in_exit},
		{"help", list_built_inshelp},
		{"cd", built_in_cd},
		{"alias", built_in_alias},
		{"env", environ_built_in},
		{"setenv", list_built_insset_env},
		{"unsetenv", list_built_insunset_env},
		{NULL, NULL}};

	/*walk through the structure*/
	for (i = 0; options[i].builtin != NULL; i++)
	{
		/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[i].builtin, data->command_name, 0))
		{
			/*execute the function, and return the return value of the function*/
			return (options[i].function(data));
		}
		/*if there is no match return -1 */
	}
	return (-1);
}

