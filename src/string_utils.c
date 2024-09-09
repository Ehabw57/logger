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

/**
 * random_ascii_char - generates a random ascii character between A-Z, a-z, 0-9
 * Return: random ascii character
 */
unsigned int random_ascii_char(void)
{
	int ranges[3][2] = {{65, 90}, {97, 122}, {48, 57}};
	int selected_range = rand() %3;
	int min = ranges[selected_range][0];
	int max = ranges[selected_range][1];

	return min + (rand() % (max -min +1));
}

/**
 * random_name - generates a random name of length between 6 and 24 characters
 * Note: the caller is responsible for freeing the memory allocated for the name
 * @name: pointer to store the generated name
 * Return: 0 on success, 1 on failure
 */
int random_name(char **name)
{
	unsigned int i = 0;
	unsigned int length = 6 + (rand() % (6 - 24));

	*name = malloc(sizeof(char) * (length +1));
	if (*name == NULL)
		return 1;

	for (i = 0; i < length; i++)
		(*name)[i] = (char)random_ascii_char();
	(*name)[length] = '\0';
	return 0;
}
