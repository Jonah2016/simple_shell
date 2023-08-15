#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>	   /* for the general printf function*/
#include <unistd.h>	   /* for mainly fork, execve methods */
#include <stdlib.h>	   /*  if a standard header file for memory allocation */
#include <string.h>	   /* for the strtok and string methods*/
#include <stddef.h>	   /* required for size_t,ptrdiff_t,NULL,offsetof */
#include <errno.h>	   /* for error regulationn - errno and perror */
#include <sys/types.h> /* for the system defined type pid */
#include <sys/wait.h>  /* for the system defined wait method */
#include <sys/stat.h>  /* for the use of the predefined stat function */
#include <signal.h>	   /* for the signal/cursor blink mgt */
#include <fcntl.h>	   /* for file opening its system defined*/

/************* CUSTOM MACROS **************/

#include "custom_macros.h" /* for msg help and prompt */

/************* CUSTOM STRUCTS **************/

/**
 * struct info- struct for the program's data
 * @application_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of make_tokend input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *application_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} application_data;

/**
 * struct built_ins - struct for the built_ins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct built_ins
{
	char *builtin;
	int (*function)(application_data *data);
} built_ins;

/************* MAIN FUNCTIONS *************/

/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void init_data(application_data *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, application_data *data);

/* Print the prompt in a new line */
void ctrl_c_handler(int opr UNUSED);

/*========  _getline.c  ========*/

/* get one line of the standard inputed value */
int _getline(application_data *data);

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *arr_commands[], int i, char arr_operators[]);

/*======== expanders.c ========*/

/* expand variables */
void variable_expander(application_data *data);

/* expand aliases */
void alias_expd(application_data *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);

/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimit */
void make_token(application_data *data);

/* Creates a pointer to a part of a string */
char *_strtokenize(char *line, char *delim);

/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(application_data *data);

/*======== list_built_ins.c ========*/

/* If match a builtin, executes it */
int list_built_ins(application_data *data);

/*======== path_finder.c ========*/

/* Creates an array of the path dirs */
char **make_token_path(application_data *data);

/* Search for program in path */
int application_finder(application_data *data);

/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

/* Frees the memory for dirs */
void array_pnts_freer(char **dirs);

/* Free the fields needed each loop */
void recurr_data_freer(application_data *data);

/* Free all field of the data */
void all_data_freer(application_data *data);

/************** built_ins **************/

/*======== more_built_ins.c ========*/

/* Close the shell */
int built_in_exit(application_data *data);

/* Change the current directory */
int built_in_cd(application_data *data);

/* set the work directory */
int set_wrkn_dir(application_data *data, char *new_dir);

/* show help information */
int list_built_inshelp(application_data *data);

/* set, unset and show alias */
int built_in_alias(application_data *data);

/*======== environ_built_ins.c ========*/

/* Shows the environment where the shell runs */
int environ_built_in(application_data *data);

/* create or override a variable of environment */
int list_built_insset_env(application_data *data);

/* delete a variable of environment */
int list_built_insunset_env(application_data *data);

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, application_data *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, application_data *data);

/* Remove a key from the environment */
int env_remove_key(char *key, application_data *data);

/* prints the current environ */
void print_environ(application_data *data);

/************** HELPERS FOR PRINTING **************/

/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _print_err(char *string);

/* Prints a string in the standar error */
int _print_error(int err_code, application_data *data);

/************** HELPERS FOR STRINGS MANAGEMENT **************/

/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* make a duplicate a str of characters */
char *str_dupl(char *string);

/* make a comparison btn two different str chars */
int str_compare(char *str1, char *str2, int number);

/* makes a concatination btn two str chars */
char *str_concatination(char *str1, char *str2);

/* make a str chars reversal */
void str_reversal(char *string);

/*======== helpers_nums.c ========*/

/* Make a type cast from int to str */
void lng_to_str(long number, char *string, int base);

/* make a conversion from a str to num */
int _atoi(char *s);

/* count the occurences of chars in a str value */
int chars_counter(char *string, char *character);

/*======== mgt_of_alias.c ========*/

/* this will print the list of the aliases */
int alias_print_errr(application_data *data, char *alias);

/* read the name of the alias  */
char *read_alias(application_data *data, char *alias);

/* write the alias name */
int write_alias(char *alias_str, application_data *data);

#endif /* _SHELL_H_ */
