#include "real_shell.h"

/**
 * exit_command - Builtin function to exit the program.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: Exit status based on the provided argument or the value of errno.
 */
int exit_command(ProgramData * data)
{
	int i;

	/* is there an existing argument for exit */
	if (data->tokens[1] != NULL)
	{/*is the argument a valid number? */
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
					&& data->tokens[1][i] != '+')
			{/* If it's not a number, errno is set and return 2 */
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data); /* Free allocated data*/
	exit(errno); /* exit with the value of errno */
}
/**
 * cd_command - Builtin function to change the current working directory.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: Error code indicating the success or failure.
 */
int cd_command(ProgramData *data)
{
	char *home_dir = env_get_key("HOME", data);
	char *old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	/* is there an exiting argument for cd*/
	if (data->tokens[1])
	{/* id the argument is a hyphen "-" */
		if (str_compare(data->tokens[1], "-", 0))
		{
			/* Retrieve the OLDPWD from env variables */
			old = env_get_key("OLDPWD", data);
			if (old) /* Change to the old working directory */
				error_code = set_work_directory(data, old);
			_printf(env_get_key("PWD", data)); /* print current working dir*/
			_printf("\n");
			return (error_code);
		}
		else /* Change to the specified directory */
			return (set_work_directory(data, data->tokens[1]));
	}
	else
	{
		if (!home_dir) /* no argument is provided ?*/
			home_dir = getcwd(old_dir, 128); /*change to the HOME*/
		return (set_work_directory(data, home_dir));
	}
	return (0);
}

/**
 * set_work_directory - Set the CWD to the specified directory.
 * @data: Pointer to the ProgramData structure containing program information.
 * @new_dir: The path to the new working directory.
 * Return: Error code indicating the success or failure.
 */
int set_work_directory(ProgramData *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	/* CWD to old_dir */
	getcwd(old_dir, 128);
	/* is the new directory is different from the current directory */
	if (!str_compare(old_dir, new_dir, 0))
	{/* Change the CWD to the new directory */
		err_code = chdir(new_dir);

		if (err_code == -1)/* has chdir errors */
		{
			errno = 2;
			return (3);  /* Return 3 to indicate chdir failure */
		}
		/* Update the "PWD" env var with the new directory */
		env_set_key("PWD", new_dir, data);
	}
	/* Update the "OLDPWD" env var with the old directory */
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * help_command - Builtin function to display help information shell commands.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: 0 on success, 1 help message is displayed, 5 on validation error.
 */
int help_command(ProgramData *data)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;
	/* Validate the number of arguments */
	if (data->tokens[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5); /* Return 5 for argument validation error */
	}
	messages[1] = HELP_MSG_EXIT;
	messages[2] = HELP_MSG_ENV;
	messages[3] = HELP_MSG_SETENV;
	messages[4] = HELP_MSG_UNSETENV;
	messages[5] = HELP_MSG_CD;

	/* does the provided argument matches any command's help message */
	for (i = 0; messages[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], messages[i], length))
		{
			_printf(messages[i] + length + 1);
			return (1);
		}
	}
	/* If no match is found, print an error and return 0 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}
/**
 * alias_command - Builtin function to manage shell aliases.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: 0 on success, or result of print_alias function.
 */
int alias_command(ProgramData *data)
{
	int i = 0;

	/* print all aliases */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	/* If arguments are present, set or print each alias */
	while (data->tokens[++i])
	{
		/* Check if the argument contains the "=" character */
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			return (print_alias(data, data->tokens[i]));
	}

	return (0);
}
