#include "shell.h"

/**
 * _print - writes a arr of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the num of bytes written or .
 * On error, -1 is returned, and errno is set correctly.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * _print_err - writes an arr of chars in the standar error
 * @string: pnt to the array of chars
 * Return: the number of bytes written or .
 *  -1 when error is detected, and errno is set correctly.
 */
int _print_err(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - write an array of chars in standart error
 * @data: a pnt to the prog data'
 * @err_code: err code to be printed
 * Return: the num of bytes written or .
 * On error, -1 will be outputed, and errno set correctly.
 */
int _print_error(int err_code, application_data *data)
{
	char num_as_str[10] = {'\0'};

	lng_to_str((long)data->exec_counter, num_as_str, 10);

	if (err_code == 2 || err_code == 3)
	{
		_print_err(data->application_name);
		_print_err(": ");
		_print_err(num_as_str);
		_print_err(": ");
		_print_err(data->tokens[0]);
		if (err_code == 2)
			_print_err(": Inccorrect number: ");
		else
			_print_err(": you can't cd to ");
		_print_err(data->tokens[1]);
		_print_err("\n");
	}
	else if (err_code == 127)
	{
		_print_err(data->application_name);
		_print_err(": ");
		_print_err(num_as_str);
		_print_err(": ");
		_print_err(data->command_name);
		_print_err(": No such file or directory\n");
	}
	else if (err_code == 126)
	{
		_print_err(data->application_name);
		_print_err(": ");
		_print_err(num_as_str);
		_print_err(": ");
		_print_err(data->command_name);
		_print_err(": Permission denied\n");
	}
	return (0);
}
