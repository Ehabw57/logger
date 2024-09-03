#include "logger.h"

/**
 * string_compare - compare two strings case-insensitively
 * @s1: first string
 * @s2: second string
 * Return: 0 if strings are equal, -1 if strings are NULL, or the difference
 */
int string_compare(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (*s1 && *s2)
	{
		char c1 = tolower((unsigned char) *s1);
		char c2 = tolower((unsigned char) *s2);

		if (c1 != c2)
			return (c1 - c2);

		s1++;
		s2++;
	}

	return (tolower((unsigned char) *s1) - tolower((unsigned char) *s2));
}

/**
 * strdup - duplicate a string
 * @str: string to duplicate
 * Return: pointer to new string, or NULL if memory allocation fails
 */
char *strdup(const char *str)
{
	char *dup = malloc(strlen(str) + 1);

	if (dup == NULL)
		return (NULL);

	strcpy(dup, str);
	return (dup);
}

