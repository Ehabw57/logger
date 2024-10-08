#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/* string mangement functions */
char *strdup(const char *str); /* Duplicates a string */
char *string_concat(char *s1, char *s2); /* Concatenates two strings */
int no_space(char *str); /* Checks if a string contains only whitespace */
int string_compare(char *s1, char *s2); /* Compares two strings */
unsigned int random_ascii_char(void); /* Generates a random ascii character */
int random_name(char **name); /* Generates a random name */
#endif // STRING_UTILS_H
