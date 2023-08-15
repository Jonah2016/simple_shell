#include "shell.h"

/**
 * str_length - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_length(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * str_dupl - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_dupl(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * str_compare - Compare two strings
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @number: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int str_compare(char *str1, char *str2, int number)
{
	int iterator;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (str_length(str1) != str_length(str2))
			return (0);
		for (iterator = 0; str1[iterator]; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (iterator = 0; iterator < number; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
}

/**
 * str_concatination - concatenates two strings.
 * @str1: String to be concatenated
 * @str2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_concatination(char *str1, char *str2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (str1 == NULL)
		str1 = "";
	length1 = str_length(str1);

	if (str2 == NULL)
		str2 = "";
	length2 = str_length(str2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of str1 */
	for (length1 = 0; str1[length1] != '\0'; length1++)
		result[length1] = str1[length1];
	free(str1);

	/* copy of str2 */
	for (length2 = 0; str2[length2] != '\0'; length2++)
	{
		result[length1] = str2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * str_reversal - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void str_reversal(char *string)
{

	int i = 0, length = str_length(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}

