#include "real_shell.h"

/**
 * execute_builtins - Execute a builtin command based on the provided data.
 * Return: Return value of the executed builtin function
 * @data: Pointer to the ProgramData structure containing program information.
 * or -1 if no match is found.
 */
int execute_builtins(ProgramData *data)
{
	int iterator;

	BuiltinCommand options[] = {
		{"exit", exit_command},
		{"help", help_command},
		{"cd", cd_command},
		{"alias", alias_command},
		{"env", env_command},
		{"setenv", set_env_command},
		{"unsetenv", env_command},
		{NULL, NULL} /* the end of the array Should always be NULL. */
	};
	/* iterate throught the array */
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/* does the given command match with one in the builtin list? */
		if (str_compare(options[iterator].builtin, data->command_name, 0))
			/* Execute the associated function and return its return value*/
			return (options[iterator].function(data));
	}
	/* Return -1 if there's no match */
	return (-1);
}
