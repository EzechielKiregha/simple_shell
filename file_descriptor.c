#include "real_shell.h"

/**
 * logic - Check for logical operators ('&&' and '||').
 * @array_of_cmds: Array of command strings.
 * @i: Index indicating the current position in the array of command strings.
 * @array_operators: Array of characters indicating the logical operators.
 * Return: Updated index after processing logical operators.
 */
int logic(char *array_of_cmds[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	/* '&' and '&&' characters in the command line*/
	for (j = 0; array_of_cmds[i] != NULL && array_of_cmds[i][j]; j++)
	{
		if (array_of_cmds[i][j] == '&' && array_of_cmds[i][j + 1] == '&')
		{
			/*Split the line when '&&' is found*/
			temp = array_of_cmds[i];
			array_of_cmds[i][j] = '\0';
			array_of_cmds[i] = str_duplicate(array_of_cmds[i]);
			array_of_cmds[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0; /*Resetting the index after splitting is important here*/
		}
		if (array_of_cmds[i][j] == '|' && array_of_cmds[i][j + 1] == '|')
		{
			/*Split the line when '||' is found*/
			temp = array_of_cmds[i];
			array_of_cmds[i][j] = '\0';
			array_of_cmds[i] = str_duplicate(array_of_cmds[i]);
			array_of_cmds[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0; /* Reset the character index after splitting */
		}
	}

	return (i); /*Return the updated index after processing logical operators*/
}
/**
 * _getline - Read a line from the file descriptor and process logic.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: Length of the read line, or -1 if the end of file is reached.
 */
int _getline(ProgramData *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_of_cmds[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t size_of_byte;
	size_t i = 0;

	/*Check if no more commands is there in the array*/
	/* and check logical operators for continuation or termination */
	if (!array_of_cmds[0] || (array_operators[0] == '&' && errno != 0) ||
			(array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; array_of_cmds[i]; i++)
		{
			free(array_of_cmds[i]);
			array_of_cmds[i] = NULL;
		}
		/*Read from the file descriptor into buff*/
		size_of_byte = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (size_of_byte == 0)
			return (-1);/* -1 if end of file is reached*/
		/*Split lines for '\n' or ';'*/
		i = 0;
		do {/* split for '&&' and '||' operators */
			array_of_cmds[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			i = logic(array_of_cmds, i, array_operators);
		} while (array_of_cmds[i++]);
	}
	/* remove the first cmd from the array*/
	data->input_line = array_of_cmds[0];
	for (i = 0; array_of_cmds[i]; i++)
	{
		array_of_cmds[i] = array_of_cmds[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (_len(data->input_line));
}
