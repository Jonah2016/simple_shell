#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(application_data *data)
{
	int responseval = 0, status;
	pid_t pidd;

	/* check for program in built ins */
	responseval = list_built_ins(data);
	if (responseval != -1)/* if program was found in built ins */
		return (responseval);

	/* check for program file system */
	responseval = application_finder(data);
	if (responseval)
	{/* if program not found */
		return (responseval);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			responseval = execve(data->tokens[0], data->tokens, data->env);
			if (responseval == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
