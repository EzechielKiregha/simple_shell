#include "real_shell.h"

/**
 * _printe - writes a array of chars in the STDERR
 * @chain_of_chars: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printe(char *chain_of_chars)
{
	return (write(STDERR_FILENO, chain_of_chars, str_length(chain_of_chars)));
}

/**
 * _printf - writes a array of chars in the STDOUT
 * @chain_of_chars: pointer to the array of characters
 * Return: the number of bytes wrote
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printf(char *chain_of_chars)
{
	return (write(STDOUT_FILENO, chain_of_chars, str_length(chain_of_chars)));
}
/**
 * _error_stdout - writes a array of chars in the STDERR
 * @data: a pointer to the ProgramData structure
 * @code_error: error code to print
 * Return: the number of bytes wrote.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _error_stdout(int code_error, ProgramData *data)
{
	char to_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, to_string, 10);

	if (code_error == 2 || code_error == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(to_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (code_error == 2)
			_printe(": Invilid number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (code_error == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(to_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (code_error == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(to_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}

