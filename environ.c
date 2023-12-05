#include "real_shell.h"


/**
 * env_command - Built-in command to manage environment variables.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: 0 on success, or appropriate error code.
 */
int env_command(ProgramData *data)
{
	int i;
	char name_container[50] = {'\0'};
	char *var_copy = NULL;

	/*If no arguments, print the environment*/
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		/*Check if there is a variable assignment*/
		for (i = 0; data->tokens[1][i] && data->tokens[1][i] != '='; i++)
			name_container[i] = data->tokens[1][i];

		if (data->tokens[1][i] == '=')
		{
			/*Temporarily change the value of an existing variable*/
			var_copy = str_duplicate(env_get_key(name_container, data));
			if (var_copy != NULL)
				env_set_key(name_container, data->tokens[1] + i + 1, data);
			/*Print the modified environment*/
			print_environ(data);
			/*Print the variable if it doesn't exist in the environment*/
			if (env_get_key(name_container, data) == NULL)
			{
				_printf(data->tokens[1]);
				_printf("\n");
			}
			else
			{
				env_set_key(name_container, var_copy, data);
				free(var_copy);
			}
			return (0);
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}


