#include "real_shell.h"

/**
 * main - initialize the variables of the program
 * @argc: number of values received in the STDIN
 * @argv: values in the STDIN
 * @env: environment array
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	ProgramData data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	data_initializer(data, argc, argv, env);

	signal(SIGINT, line_prompt);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	my_shell(prompt, data);
	return (0);
}

/**
 * data_initializer - initialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void data_initializer(ProgramData *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
		for (; env[i]; i++)
			data->env[i] = str_duplicate(env[i]);
	data->env[i] = NULL;
	env = data->env;

	data->aliases = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
		data->aliases[i] = NULL;
}

/**
 * line_prompt - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void line_prompt(int opr UNUSED)
{
	_printf("\n");
	_printf(PROMPT_MSG);
}
/**
 * my_shell - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void my_shell(char *prompt, ProgramData *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_printf(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_the_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* execute */
				error_code = execute(data);
				if (error_code != 0)
					_error_stdout(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
