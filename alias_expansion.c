#include "real_shell.h"

/**
 * add_to_buffer - Append a string to a buffer.
 * @buffer: The buffer is appended the string.
 * @str_to_add: The string to append to the buffer.
 * Return: The new length of the buffer.
 */
int add_to_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = _len(buffer);
	for (i = 0; str_to_add[i]; i++)
		buffer[length + i] = str_to_add[i];

	buffer[length + i] = '\0'; /*add a nul terminator*/

	return (length + i); /*the new length of the buffer is returned*/
}
/**
 * expand_alias - Expand aliases in the input line.
 * @data: Pointer to the ProgramData structure.
 * Return: None.
 */
void expand_alias(ProgramData *data)
{
	int i, j, expanded = 0;
	char line[BUFFER_SIZE] = {0}, var_expand[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	add_to_buffer(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		/* Extract the potential alias name */
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			var_expand[j] = line[i + j];
		var_expand[j] = '\0';

		/* Get the value of the alias from the alias list */
		temp = alias_get(data, var_expand);

		/* If the alias is found, expand it in the line */
		if (temp)
		{
			/* Update the line with the expanded alias */
			var_expand[0] = '\0';
			add_to_buffer(var_expand, line + i + j);
			line[i] = '\0';
			add_to_buffer(line, temp);
			line[_len(line)] = '\0';
			add_to_buffer(line, var_expand);
			expanded = 1;
		}
		break; /* Stop after the first alias var_expand */
	}

	/* Check if the input line has changed and update it */
	if (expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
