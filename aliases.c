#include "real_shell.h"

/**
 * print_alias - Print aliases or a specific alias if provided.
 * @data: Pointer to the ProgramData structure.
 * @alias: Specific alias to print.
 * Return: 0 on success.
 */
int print_alias(ProgramData *data, char *alias)
{
	char buffer[250] = {'\0'};
	int i, j, len;

	/* Check if aliases exists */
	if (data->aliases)
	{
		len = _len(alias);
		for (i = 0; data->aliases[i]; i++)
		{
			if (!alias || (str_compare(data->aliases[i], alias, len)
						&& data->aliases[i][len] == '='))
			{
				/* Copy alias until '=' to buffer */
				for (j = 0; data->aliases[i][j] && data->aliases[i][j] != '='; j++)
					buffer[j] = data->aliases[i][j];

				buffer[j + 1] = '\0';
				add_to_buffer(buffer, "'");
				add_to_buffer(buffer, data->aliases[i] + j + 1);
				add_to_buffer(buffer, "'\n");
				_printf(buffer);
			}
		}
	}

	return (0);
}
/**
 * alias_get - Get the value associated with a given alias name.
 * @data: Pointer to the ProgramData structure.
 * @name: Name of the alias to retrieve.
 * Return: The value associated with the alias, or NULL if not found.
 */
char *alias_get(ProgramData *data, char *name)
{
	int i, len;

	/* Validate arguments */
	if (name == NULL || data->aliases == NULL)
		return (NULL);
	len = _len(name);
	for (i = 0; data->aliases[i]; i++)
	{
		/* any match so far in alias name and the format 'NAME=' */
		if (str_compare(name, data->aliases[i], len) &&
				data->aliases[i][len] == '=')
			/* Return the value associated with the alias */
			return (data->aliases[i] + len + 1);
	}
	/* NULL is returned if the alias is not found */
	return (NULL);
}

/**
 * alias_set - Set or update an alias.
 * @str_alias: String containing the alias name and value.
 * @data: Pointer to the ProgramData structure.
 * Return: 0 on success, 1 if invalid arguments.
 */
int alias_set(char *str_alias, ProgramData *data)
{
	char buffer[250] = {'\0'}, *temp = NULL;
	int i, j;

	if (str_alias == NULL || data->aliases == NULL)
		return (1);
	/* Iterate through str_alias to find '=' character */
	for (i = 0; str_alias[i]; i++)
	{
		if (str_alias[i] != '=')
		{
			buffer[i] = str_alias[i];
		}
		else
		{/* Search if the value of the alias is another alias */
			temp = alias_get(data, str_alias + i + 1);
			break;
		}
	}
	for (j = 0; data->aliases[j]; j++)
	{
		if (str_compare(buffer, data->aliases[j], i) &&
				data->aliases[j][i] == '=')
		{/* If the alias already exists, free the old value */
			free(data->aliases[j]);
			break;
		}
	}
	if (temp) /* Add the alias */
	{
		add_to_buffer(buffer, "=");
		add_to_buffer(buffer, temp);
		data->aliases[j] = str_duplicate(buffer);
	}
	else /* If the alias does not exist, set it */
		data->aliases[j] = str_duplicate(str_alias);

	return (0);
}
