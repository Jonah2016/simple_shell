#include "shell.h"
/**
 * main - init the main vars of the prog
 * @argc: num of chars received from the command line
 * @argv: values received from the command line
 * @env: number of env vars values received from command line
 * Return: 0 when successful.
 */
int main(int argc, char *argv[], char *env[])
{
	application_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{			   /* We are in the terminal, interactive mode */
		errno = 2; /*???????*/
		prompt = CUSTOM_PROMPT_MESSAGE;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * ctrl_c_handler - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the prog
 * @UNUSED: option of the prototype
 */
void ctrl_c_handler(int opr UNUSED)
{
	_print("\n");
	_print(CUSTOM_PROMPT_MESSAGE);
}

/**
 * init_data - init the struct with the info of the prog
 * @data: pnt to the struct of data
 * @argv: arr of args passed to the prog exec
 * @env: env pased to the prog exec
 * @argc: num of vals received from the command line
 */
void init_data(application_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->application_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_print_err(data->application_name);
			_print_err(": 0: Can't open ");
			_print_err(argv[1]);
			_print_err("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (data->env == NULL)
		exit(1);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_dupl(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	if (data->alias_list == NULL)
		exit(1);
	for (i = 0; i < 20; i++)
		data->alias_list[i] = NULL;
}
/**
 * sisifo - an infinite loop that displays the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that displays the prompt
 */
void sisifo(char *prompt, application_data *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			all_data_freer(data);
			exit(errno); /* if EOF is 1st char of str, exit*/
		}
		if (string_len >= 1)
		{
			alias_expd(data);
			variable_expander(data);
			make_token(data);
			if (data->tokens[0])
			{ /* if a txt is given to prompt, exec */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			recurr_data_freer(data);
		}
	}
}

