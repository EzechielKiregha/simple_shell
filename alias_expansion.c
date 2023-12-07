#include "real_shell.h"

/**
 * expand_the_variable - Expand variables in the input line.
 * @data: Pointer to the ProgramData structure.
 * Return: None.
 */
void expand_the_variable(ProgramData *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, var_expand[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_to_buffer(line, data->input_line);
	for (i = 0; line[i]; i++)
	{/* Handle '#' as a comment indicator*/
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{/*Expand '$?' with the value of errno */
			line[i] = '\0';
			long_to_string(errno, var_expand, 10);
			add_to_buffer(line, var_expand);
			add_to_buffer(line, data->input_line + i + 2);
		} /* Expand '$$' with the process ID */
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), var_expand, 10);
			add_to_buffer(line, var_expand);
			add_to_buffer(line, data->input_line + i + 2);
		} /* Skip '$ ' or '$' at the end of the line */
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$') /* Expand other variables starting with '$' */
		{ /*Extract the variable name */
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				var_expand[j - 1] = line[i + j];
			temp = env_get_key(var_expand, data);
			line[i] = '\0';/* Update the line with the expanded variable */
			var_expand[0] = '\0';
			add_to_buffer(var_expand, line + i + j);
			temp ? add_to_buffer(line, temp) : 1;
			add_to_buffer(line, var_expand);
		}
	} /* Check if the input line has changed and update it */
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * add_to_buffer - Append a string to a buffer.
 * @buffer: The buffer is appended the string.
 * @str_to_add: The string to append to the buffer.
 * Return: The new length of the buffer.
 */
int add_to_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
		buffer[length + i] = str_to_add[i];

	buffer[length + i] = '\0'; /*add a nul terminator*/

	return (length + i); /*the new length of the buffer is returned*/
}
