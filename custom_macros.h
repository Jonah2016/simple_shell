#ifndef CUSTOM_HELPERS_H
#define CUSTOM_HELPERS_H

/* Prompt to be printed */
#define CUSTOM_PROMPT_MESSAGE "$" /* Needed to work with signal */

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFF_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define CD_HELP_MESSAGE "cd=\n"\
	"cd:\tcd [dir]\n\n"\
	"Please change the working directory of the shell.\n\n"\
	"If empty argument is given for cd, this command will \n"\
	"be executed as cd $HOME.\n"\
	"if the input help is - (cd -), the command will be executed\n"\
	"as cd $OLDPWD.\n\n"

#define EXIT_HELP_MESSAGE "exit=\n"\"exit:\texit [STATUS]\n\n"\
	"Exiting the simple-shell app.\n\n"\
	"Exits the custom shell with a status of N. If N is omitted, \n"\
	"the exit status is that of the last command executed.\n\n"

#define ENV_HELP_MESSAGE "env=\n"\
	"env:\tenv \n\n"\
	"Print environment variables.\n\n"\
	"The env command should print a complete list of env vars.\n\n"

#define SET_ENV_HELP_MESSAGE "setenv=\n"\
	"setenv:\tsetenv VARIABLE VALUE\n\n"\
	"Change or add an environment variable.\n\n"\
	"initialize a new environment variable, or modify an existing one.\n"\
	"When there are not correct numbers of arguments print an error msg.\n\n"

#define UNSET_ENV_HELP_MESSAGE "unsetenv=\n"\
	"unsetenv:\tunsetenv VARIABLE\n\n"\
	"The unsetenv function deletes one var from the env.\n\n"\
	"If there are not accurate nums of args print an error msg.\n\n"

#define HELP_MESSAGE "help=\n"\
	"help:\thelp [BUILT_IN_NAME]\n\n"\
	"Display info about builtin commands.\n\n"\
	"Display a brief summary of builtin commands.\n"\
	"If the BUILT_IN_NAME is given, give detailed help on all commands \n"\
	"that match the BUILT_IN_NAME, otherwise the list of.\n"\
	"help topics will be printed in the BUILT_IN_NAME list.\n"\
	"Arguments:\n\n"\
	"BUILT_IN_NAME specifiying a help topic.\n\n"\
	"cd\t[dir]\n"\
	"exit\t[status]\n"\
	"env\n"\
	"setenv\t[variable value]\n"\
	"unset\t[variable]\n"\
	"help\t[built_name]\n\n"

#endif

