#include "real_shell.h"

/**
 * count_characters - count the coincidences of character in string.
 *
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
		if (string[i] == character[0])
			counter++;

	return (counter);
}
/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int operator = 1;
	unsigned int number = 0;
	/*1- analisys operator*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			operator *= -1;
		if (*s == '+')
			operator *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * operator);
}

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @_base: base to convert number
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int _base)
{
	int index = 0, inNegative = 0;
	long operand = number;
	char array_hexa[] = {"0123456789abcdef"};

	if (operand == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (operand)
	{
		if (operand < 0)
			string[index++] = array_hexa[-(operand % _base)];
		else
			string[index++] = array_hexa[operand % _base];
		operand /= _base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}
