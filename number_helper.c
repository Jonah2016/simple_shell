#include "shell.h"

/**
 * lng_to_str - convert the num to a str.
 * @number: num to be converten in an str.
 * @string: buff to save the num as str.
 * @base: base to convert num
 *
 * Return: Nothing.
 */
void lng_to_str(long number, char *string, int base)
{
	int ind = 0, inNeg = 0;
	long quotient = number;
	char alphabets[] = {"0123456789abcdef"};

	if (quotient == 0)
		string[ind++] = '0';

	if (string[0] == '-')
		inNeg = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[ind++] = alphabets[-(quotient % base)];
		else
			string[ind++] = alphabets[quotient % base];
		quotient /= base;
	}
	if (inNeg)
		string[ind++] = '-';

	string[ind] = '\0';
	str_reversal(string);
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int symbol = 1;
	unsigned int number = 0;
	/*1- analysis symbol*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			symbol *= -1;
		if (*s == '+')
			symbol *= +1;
		s++;
	}

	/*2 - extracting the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * symbol);
}

/**
 * chars_counter - count the coincidences of character in string.
 *
 * @string: pointer to string origin.
 * @character: str with  characters to be counted
 * Return: int of the str or 0 value.
 */
int chars_counter(char *string, char *character)
{
	int i = 0, cnt = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			cnt++;
	}
	return (cnt);
}
