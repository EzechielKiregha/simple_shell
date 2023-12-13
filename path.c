#include "real_shell.h"

/* File_checking signature*/
int file_checking(char *path);

/**
 * locate_executable_cmd - Find path of the cmd in the file system.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: 0 cmd is executable, 126 executable, 127 not found.
 */
int locate_executable_cmd(ProgramData *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (file_checking(data->command_name));

	/* Construct a full path using the command_name */
	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);

	/* Check if memory allocation fails */
	if (!data->tokens[0])
		return (2);

	/* Tokenize the PATH environment variable */
	directories = path_tok(data);
	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	/* Iterate through each directory in PATH */
	for (i = 0; directories[i]; i++)
	{
		/* Append the command to path */
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = file_checking(directories[i]);

		/* is file found? not a directory?,has it execute permissions? */
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(&(directories));
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(&(directories));
	return (ret_code);
}

/**
 * **path_tok - Tokenize the PATH env var into an array of directories.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: An array of directory paths, or NULL if PATH is not set.
 */
char **path_tok(ProgramData *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = get_env_key("PATH", data);

	/* Check if PATH is not set or empty */
	if (PATH[0] == '\0' || PATH == NULL)
		return (NULL);
	PATH = str_duplicate(PATH);
	for (i = 0; PATH[i]; i++)
		if (PATH[i] == ':')
			counter_directories++;

	/* Allocate space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	/* Clean and return */
	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * file_checking - Check if a file exists and is executable.
 * @path: Full path to the file.
 * Return: 0 executable, 126 executable, 127 not found.
 */
int file_checking(char *path)
{
	struct stat st;

	/* does the file exists?if yes, get its stat information */
	if (stat(path, &st) != -1)
	{
		if (S_ISDIR(st.st_mode) || access(path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}
