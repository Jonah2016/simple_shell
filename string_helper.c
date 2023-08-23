#include "shell.h"

/**
 * str_length - returns the len of a string.
 * @string: pointer to string.
 * Return: len of string.
 */
int str_length(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_dupl - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_dupl(char *string)
{
	char *res;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_length(string) + 1;

	res = malloc(sizeof(char) * len);

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len; i++)
	{
		res[i] = string[i];
	}

	return (res);
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
	int i;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (number == 0) /* infinite longitude */
	{
		if (str_length(str1) != str_length(str2))
			return (0);
		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (i = 0; i < number; i++)
		{
			if (str1[i] != str2[i])
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
	char *res;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_length(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = str_length(str2);

	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL || res == '\0')
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of str1 */
	for (len1 = 0; str1[len1] != '\0'; len1++)
		res[len1] = str1[len1];
	free(str1);

	/* copy of str2 */
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		res[len1] = str2[len2];
		len1++;
	}

	res[len1] = '\0';
	return (res);
}

/**
 * str_reversal - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void str_reversal(char *string)
{

	int i = 0, len = str_length(string) - 1;
	char pause;

	while (i < len)
	{
		pause = string[i];
		string[i++] = string[len];
		string[len--] = pause;
	}
}
