#include "real_shell.h"

/**
 * _strtok - separates strings with delimiters
 * @line: ItÂ´s pointer to array we receive in getline.
 * @delim: ItÂ´s characters we mark off string in parts.
 * Return: A pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copy;

	if (line != NULL)
		str = line;

	while (*str != '\0')
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}

		if (delim[j] == '\0')
			break;

		str++;
	}
	copy = str;
	if (*copy == '\0')
		return (NULL);

	while (*str != '\0')
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copy);
			}
		}
		str++;
	}

	return (copy);
}
