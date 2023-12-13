#include "real_shell.h"

/**
 * str_duplicate - duplicates an string
 * @chain_of_chars: String to be copied
 * Return: pointer to the array
 */
char *str_duplicate(char *chain_of_chars)
{
	char *result;
	int length, i;

	if (chain_of_chars == NULL)
		return (NULL);

	length = _len(chain_of_chars) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = chain_of_chars[i];
	}

	return (result);
}

/**
 * _len - returns the length of a string.
 * @chain_of_chars: pointer to string.
 * Return: length of string.
 */
int _len(char *chain_of_chars)
{
	int length = 0;

	if (chain_of_chars == NULL)
		return (0);

	while (chain_of_chars[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * str_compare - Compare two strings
 * @chain_of_chars_1: String one, or the shorter
 * @chain_of_chars_2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int str_compare(char *chain_of_chars_1, char *chain_of_chars_2, int number)
{
	int iterator;

	if (chain_of_chars_1 == NULL && chain_of_chars_2 == NULL)
		return (1);

	if (chain_of_chars_1 == NULL || chain_of_chars_2 == NULL)
		return (0);

	if (number == 0)
	{
		if (_len(chain_of_chars_1) != _len(chain_of_chars_2))
			return (0);
		for (iterator = 0; chain_of_chars_1[iterator]; iterator++)
		{
			if (chain_of_chars_1[iterator] != chain_of_chars_2[iterator])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (chain_of_chars_1[iterator] != chain_of_chars_2[iterator])
				return (0);
		}
		return (1);
	}
}
/**
 * str_reverse - reverses a string.
 * @chain_of_chars: pointer to string.
 * Return: void.
 */
void str_reverse(char *chain_of_chars)
{

	int i = 0, length = _len(chain_of_chars) - 1;
	char container;

	while (i < length)
	{
		container = chain_of_chars[i];
		chain_of_chars[i++] = chain_of_chars[length];
		chain_of_chars[length--] = container;
	}
}
/**
 * str_concat - concatenates two strings.
 * @chain_of_chars_1: String to be concatenated
 * @chain_of_chars_2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_concat(char *chain_of_chars_1, char *chain_of_chars_2)
{
	char *result;
	int len1 = 0, len2 = 0;

	if (chain_of_chars_1 == NULL)
		chain_of_chars_1 = "";
	len1 = _len(chain_of_chars_1);

	if (chain_of_chars_2 == NULL)
		chain_of_chars_2 = "";
	len2 = _len(chain_of_chars_2);

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of chain_of_chars_1 */
	for (len1 = 0; chain_of_chars_1[len1] != '\0'; len1++)
		result[len1] = chain_of_chars_1[len1];
	free(chain_of_chars_1);

	/* copy of chain_of_chars_2 */
	for (len2 = 0; chain_of_chars_2[len2] != '\0'; len2++)
	{
		result[len1] = chain_of_chars_2[len2];
		len1++;
	}

	result[len1] = '\0';
	return (result);
}

