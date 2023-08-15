#include "shell.h"

/**
 * env_get_key - gets the value of an env var
 * @key: the env var of interest
 * @data: struct of the prog data
 * Return: a pnt to the value of the var or NULL if it doesn't exist
 */
char *env_get_key(char *key, application_data *data)
{
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{ /* Iterates on the env and check for occurences of the vame */
		if (str_compare(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{ /* returns the value of the key NAME=  when find it*/
			return (data->env[i] + key_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the env var
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the prog data
 * Return: 1 if the params are NULL, 2 if there is an error or 0 if success.
 */

int env_set_key(char *key, char *value, application_data *data)
{
	int i, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the len of the var requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{ /* Iterates through the env and check for occurence of the vame */
		if (str_compare(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{ /* If key already exists */
			is_new_key = 0;
			/* free the entire var, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* make an str of the form key=value */
	data->env[i] = str_concatination(str_dupl(key), "=");
	data->env[i] = str_concatination(data->env[i], value);

	if (is_new_key)
	{	/* if the var is new, it is create at end of actual list and we need*/
		/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the env
 * @key: the key to remove
 * @data: the sruct of the prog data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, application_data *data)
{
	int i, key_length = 0;

	/* validate the args */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the len of the var requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{ /* iterates in the env and checks for occurences */
		if (str_compare(key, data->env[i], key_length) &&
			data->env[i][key_length] == '=')
		{ /* if key already exists, remove them */
			free(data->env[i]);

			/* move the other keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the new end of the list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_environ - prints the current env
 * @data: struct for the prog data
 * Return: void
 */
void print_environ(application_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
