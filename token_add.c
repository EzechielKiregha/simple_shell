#include "real_shell.h"

/**
 * tokenize - Tokenize the input line into an array of strings.
 * @data: Pointer to the ProgramData's data structure.
 *
 * This function tokenizes the input line using the specified delimiters
 * and stores the resulting tokens in the data structure.
 */
void tokenize(ProgramData *data)
{
	char *delimiter = " \t";
	int i = 0, j = 0, counter = 2, length;

	length = _len(data->input_line);

	/* Remove the newline character at the end, if present */
	if (length && data->input_line[length - 1] == '\n')
		data->input_line[length - 1] = '\0';

	/* Count the number of tokens based on delimiters */
	while (data->input_line[i])
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				counter++;
		}
		i++;
	}

	/* Allocate memory for the tokens array */
	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	/* Initialize variables and tokenize the line */
	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);

	/* Continue tokenizing the input line */
	while (data->tokens[i++])
		data->tokens[i] = str_duplicate(_strtok(NULL, delimiter));
}
