#include "real_shell.h"

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: struct of the ProgramData structure
 * Return: Nothing
 */
void free_recurrent_data(ProgramData *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}
/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @list: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char **list)
{
	int i;

	if (list != NULL)
	{
		for (i = 0; list[i]; i++)
			free(list[i]);

		free(list);
		list = NULL;
	}
}
/**
 * free_all_data - free all field of the data
 * @data: struct of the ProgramData structure
 * Return: Nothing
 */
void free_all_data(ProgramData *data)
{
	if (data->file_descriptor != 0)
		if (close(data->file_descriptor))
			perror(data->program_name);

	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->aliases);
}
