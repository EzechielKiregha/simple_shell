#include "real_shell.h"

/**
 * execute - Execute a command, searching in built-ins and the file system.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: 0 on success, -1 on failure.
 */
int execute(ProgramData *data)
{
	int value = 0, status;
	pid_t pid;

	/* Check if the command is a built-in */
	value = is_builtin(data);
	if (value != -1)
	{/*isbuiltin? execute it and return its result*/
		return (value);
	}
	value = locate_executable_cmd(data);
	if (value)
	{/* If not found, return the error code */
		return (value);
	}
	pid = fork();/*fork a new process, if found*/
	if (pid == -1)
	{/* If fork fails, print an error and exit */
		perror(data->command_name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{ /* Child process: execute the program */
		value = execve(data->tokens[0], data->tokens, data->env);
		if (value == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{/* Parent process: once child complete and check its exit status */
		wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
	}
	return (0);
}
