#ifndef REAL_SHELL_H
#define REAL_SHELL_H

/* ---------- shell_support.h -------------*/ 
#include "shell_support.h"

#include <stdio.h>    /* Standard I/O functions, used for printf */
#include <unistd.h>   /* POSIX API, including fork, execve */
#include <stdlib.h>   /* Standard Library , for memory allocation */
#include <string.h>   /* String manipulation, including strtok */
#include <stddef.h>   /* Standard definitions, for typedef */
#include <errno.h>    /* includes errno and perror to check the errors */
#include <sys/types.h> /* including pid_t */
#include <sys/wait.h> /* includes wait functions */
#include <sys/stat.h> /* for stat function */
#include <signal.h>   /* Signal handling and management */
#include <fcntl.h>    /* used for open files */

/**
 * struct ProgramData- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */

typedef struct ProgramData
{
	char *program_name;
	char *input_line;
	char *command_name;
	char **tokens;
	char **env;
	char **alias_list;
	int exec_counter;
	int file_descriptor;
} ProgramData;


/**
 * struct BuiltinCommand - builtin command & its associated function.
 * @builtin: name of the builtin command.
 * @function: pointer to the associated function for the builtin command.
 */
typedef struct BuiltinCommand
{
    char *builtin;
    int (*function)(ProgramData *data);
} BuiltinCommand;

/* ------- builtin_command_list.c -------- */

int exit_command(ProgramData *data);
int cd_command(ProgramData *data);
int set_work_directory(ProgramData *data, char *new_dir);
int help_command(ProgramData *data);
int alias_command(ProgramData *data);
int env_command(ProgramData *data);
int set_env_command(ProgramData *data);
int unset_env_command(ProgramData *data);

/* Execute the builtins commands */
int is_builtin(ProgramData *data);

/* ---------- path.c ------------- */

/* Find the executable program */
int locate_executable_cmd(ProgramData *data);

/* Create Array of tokenized directories*/
char **path_tok(ProgramData *data);

/* -------- file_descriptor.c --------- */

/* split the each line for the logical operators if it exist */
int logic(char *array_commands[], int i, char array_operators[]);

/* Read one line from file descriptor*/
int _getline(ProgramData *data);

/* ---------- eviron.c ----------- */

/* Shows the environment where the shell runs */
int env_command(ProgramData *data);

#endif
