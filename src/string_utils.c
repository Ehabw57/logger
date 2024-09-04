#include "string_utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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

/**
 * string_concat - concatenate two strings
 * @s1: first string
 * @s2: second string
 * Return: pointer to new string, or NULL if memory allocation fails
 */
char *string_concat(char *s1, char *s2)
{
	char *concat;
	int len1 = s1 ? strlen(s1) : 0;
	int len2 = s2 ? strlen(s2) : 0;

	concat = malloc(len1 + len2 + 1);
	if (concat == NULL)
		return (NULL);

	if (s1)
		strcpy(concat, s1);
	if (s2)
		strcpy(concat + len1, s2);

	return (concat);
}

/**
 * no_space - check if a string contains spaces
 * @str: string to check
 * Return: 1 if string contains no spaces, 0 if it does
 */
int no_space(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (0);
		str++;
	}

	return (1);
}
