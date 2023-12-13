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
 * @aliases: array of pointers with aliases.
 */

typedef struct ProgramData
{
	char *program_name;
	char *input_line;
	char *command_name;
	char **tokens;
	char **env;
	char **aliases;
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

/*Execute a command, searching in built-ins and the file system*/
int execute(ProgramData *data);

/* ----------- mainloop.c --------- */

/* Inicialize the struct with the info of the program */
void data_initializer(ProgramData *data, int argc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void my_shell(char *prompt, ProgramData *data);

/* Print the prompt in a new line */
void line_prompt(int opr UNUSED);
/* ---------- path.c ------------- */

/* Find the executable program */
int locate_executable_cmd(ProgramData *data);

/* Create Array of tokenized directories*/
char **path_tok(ProgramData *data);

/*--------- aliases.c ------------*/

/* print aliases or a specific alias if provided */
int print_alias(ProgramData *data, char *alias);

/* get the value associated with the given alias*/
char *alias_get(ProgramData *data, char *name);

/* set or update the existing alias */
int alias_set(char *str_alias, ProgramData *data);


/* -------- file_descriptor.c --------- */

/* split the each line for the logical operators if it exist */
int logic(char *array_commands[], int i, char array_operators[]);

/* Read one line from file descriptor*/
int _getline(ProgramData *data);

/* ---------- eviron.c ----------- */

/* Shows the environment where the shell runs */
int env_command(ProgramData *data);

/* create or override a variable of environment */
int set_env(ProgramData *data);

/* delete a variable of environment */
int unset_env(ProgramData *data);

/*-------------- manage_env.c ------------*/

/* Remove a key from the environment */
int remove_env_key(char *key, ProgramData *data);

/* prints the current environ */
void print_env(ProgramData *data);

/* Gets the value of an environment variable */
char *get_env_key(char *key, ProgramData *data);

/* Overwrite the value of the environment variable */
int set_key_value_pair(char *key, char *value, ProgramData *data);

/*------------- alias_expansion.c -------------*/

/* Expand variables in the input line*/
void expand_the_variables(ProgramData *data);

/* expand aliases */
void expand_alias(ProgramData *data);

/* append the string to the end of the buffer*/
int add_to_buffer(char *buffer, char *str_to_add);

/*--------------- token_add.c & tokenization.c --------------*/

/*Tokenize the input line into an array of strings.*/
void tokenize(ProgramData *data);


/*separates strings with delimiters*/
char *_strtok(char *line, char *delim);

/*------------ print_out.c / helper print------------*/

/*writes a array of characters in the STDOUT*/
int _printf(char *chain_of_chars);

/*writes a array of characters in the STDERR*/
int _printe(char *chain_of_chars);

/*writes a array of chars in the STDERR*/
int _error_stdout(int code_error, ProgramData *data);

/*--------- chain_of_chars.c / helper string ---------*/

/* Counts the number of characters of a string */
int _len(char *chain_of_chars);

/* Duplicates an string */
char *str_duplicate(char *chain_of_chars);

/* Compares two strings */
int str_compare(char *chain_of_chars_1, char *chain_of_chars_2, int number);

/* Concatenates two strings */
char *str_concat(char *chain_of_chars_1, char *chain_of_chars_2);

/* Reverse a string */
void str_reverse(char *chain_of_chars);

/*-------- numbers.c / helper number ----------*/

/* Cast from int to string */
void long_to_string(long number, char *string, int _base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);

/*-------- memory_release.c / helper free ------------*/

/* the memory for directories released (freed)*/
void free_array_of_pointers(char ***list);

/* Free the fields needed each loop */
void free_recurrent_data(ProgramData *data);

/* Free all field of the data */
void free_all_data(ProgramData *data);

#endif
