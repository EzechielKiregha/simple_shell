#include "real_shell.h"

/**
 * expand_errno - Expand '$?' with the value of errno
 * @line: Buffer to store the expanded line
 */
static void expand_errno(char *line)
{
	long_to_string(errno, line, 10);
}

/**
 * expand_process_id - Expand '$$' with the process ID
 * @line: Buffer to store the expanded line
 */
static void expand_process_id(char *line)
{
	long_to_string(getpid(), line, 10);
}

/**
 * expand_variable - Expand variables starting with '$'
 * @data: Program data
 * @line: Buffer to store the expanded line
 * @var: Buffer to store the variable name
 * @i: Current index in the line
 */
static void expand_variable(ProgramData *data, char *line, char *var, int *i)
{
	int j;
	char *temp;

	/* Extract the variable name */
	for (j = 1; line[*i + j] && line[*i + j] != ' '; j++)
		var[j - 1] = line[*i + j];

	temp = get_env_key(var, data);
	line[*i] = '\0'; /* Update the line with the expanded variable */
	var[0] = '\0';

	add_to_buffer(var, line + *i + j);
	temp ? add_to_buffer(line, temp) : 1;
	add_to_buffer(line, var);
}

/**
 * expand_the_variables - Expand variables in the input line
 * @data: Program data
 */
void expand_the_variables(ProgramData *data)
{
	int i;
	char line[BUFFER_SIZE] = {0}, var[BUFFER_SIZE] = {'\0'};

	if (data->input_line == NULL)
		return;

	add_to_buffer(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
			expand_errno(line);
		else if (line[i] == '$' && line[i + 1] == '$')
			expand_process_id(line);
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
			expand_variable(data, line, var, &i);
	}

	/* Check if the input line has changed and update it */
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
