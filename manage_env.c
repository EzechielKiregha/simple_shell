#include "real_shell.h"

/**
 * set_key_value_pair - Set or update an environment variable key-value pair.
 * @key: Name of the environment variable to set or update.
 * @value: Value to associate with the key.
 * @data: Pointer to the ProgramData structure.
 * Return: 0 on success, 1 if invalid arguments.
 */
int set_key_value_pair(char *key, char *value, ProgramData *data)
{
	int i, len = 0, does_it_exist = 1;

	/* Validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	len = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], len) &&
				data->env[i][len] == '=')
		{ /* If key already exists, free the entire variable and break*/
			does_it_exist = 0;
			free(data->env[i]);
			break;
		}
	}

	/* Create a string of the form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (does_it_exist)
		/* If the variable is new, set NULL in the next position */
		data->env[i + 1] = NULL;

	return (0);
}

/**
 * get_env_key - Get the value associated with a given env var key.
 * @key: Name of the environment variable to retrieve.
 * @data: Pointer to the ProgramData structure.
 * Return: The value associated with the key, or NULL if not found.
 */
char *get_env_key(char *key, ProgramData *data)
{
	int i, len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	/* Obtain the length of the variable requested*/
	len = str_length(key);

	/* Iterate through the env for any the coincidence of the name */
	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], len) &&
				data->env[i][len] == '=')
			/* Return the value associated with the key */
			return (data->env[i] + len + 1);
	}

	/* NULL is returned if the key is not found*/
	return (NULL);
}

/**
 * remove_env_key - Remove an environment variable by key.
 * @key: Name of the environment variable to remove.
 * @data: Pointer to the ProgramData structure.
 * Return: 1 on success, 0 if the key is not found or invalid arguments.
 */
int remove_env_key(char *key, ProgramData *data)
{
	int i, len = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	len = str_length(key);

	/ Iterate through the environment maybe for coincidences /
		for (i = 0; data->env[i]; i++)
		{
			if (str_compare(key, data->env[i], len) &&
					data->env[i][len] == '=')
			{
				/* If the key exists, remove it and shift others down */
				free(data->env[i]);

				/* Move the other keys one position down */
				i++;
				for (; data->env[i]; i++)
					data->env[i - 1] = data->env[i];

				/ Put NULL at the new end of the list /
					data->env[i - 1] = NULL;
				return (1);
			}
		}

	return (0); / Return key not found or invalid arguments /
}

/**
 * print_env - Print the current env var.
 * @data: Pointer to the ProgramData structure.
 * Return: None.
 */
void print_env(ProgramData *data)
{
	int j;

	/*Iterate through the env and print each variable */
	for (j = 0; data->env[j]; j++)
	{
		_printf(data->env[j]);
		_printf("\n");
	}
}

These prototypes are to be added in the header file real_shell.h

code :

/* Remove a key from the environment */
int remove_env_key(char *key, ProgramData *data);

/* prints the current environ */
void print_env(ProgramData *data);

/* Gets the value of an environment variable */
char *get_env_key(char *key, ProgramData *data);

/* Overwrite the value of the environment variable */
int set_key_value_pair(char *key, char *value, ProgramData *data);
