#include "input.h"
#include "db_essentials.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

/**
 * exit_handler - Handel all program exit status
 * @line; Read line
 * @tokens: tokens of the line
 */
void exit_handler(sqlite3 *db, char **line, char **tokens)
{

	close_connection(db);
	if (*line != NULL && !feof(stdin))
		free(*line);
	if(tokens != NULL && !feof(stdin))
		free(tokens);
	printf("\n---------Goodbye---------\n");
}

/**
 * Reads a line from a given input stream.
 * @stream: The input stream to read from.
 * Return: A dynamically allocated string containing the line read from the stream.
 *         Returns NULL if the end of the file is reached.
 */
char *read_line(FILE* stream)
{
	size_t size = BUFFER_SIZE;
	int nread;
    char *line = malloc(sizeof(char) * BUFFER_SIZE);

	if (line == NULL) 
		return(NULL);

	nread = getline(&line, &size, stream); /*get a line from the stream*/
	if (nread == -1) 
	{
		free(line);
		if (feof(stream)) /*if the stream reached EOF return*/
				return (NULL);
		exit(EXIT_FAILURE); /*else this means that getline made an error*/
	}

	line[nread - 1] = '\0'; /*convert the newline aka(\n) to null termnatior*/
    return line;
}
/**
 * get_passwd - reads a password from the stream without echoing it
 * Note: the caller is responsible for freeing the memory allocated for the password
 * @stream: stream to read the password from
 * Return: password on success, NULL on failure
 */
char *get_passwd(FILE *stream)
{
    struct termios old, new;
	char *passwd = NULL;

    /* Turn echoing off and fail if we can't. */
    if (tcgetattr (fileno (stream), &old) != 0)
        return NULL;
    new = old;
    new.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stream), TCSAFLUSH, &new) != 0)
        return NULL;

    /* Read the password. */
    passwd = read_line(stream);
	if (passwd == NULL)
	{
		(void) tcsetattr (fileno (stream), TCSAFLUSH, &old);
		return NULL;
	}

    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old);

    return passwd;
}

/**
 * Tokenizes a given line into individual tokens separated by spaces.
 * @line; The input string to tokenize.
 * Return: A dynamically allocated array of strings (tokens).
 */
char **tokenize_line(char *line)
{
    int i = 0;
    char **tokens = malloc(sizeof(char *) * 6);  /* you have to Dynamic allocation for tokens*/

    if (tokens == NULL)
        return NULL;

    tokens[0] = strtok(line, " ");
    while (tokens[i] != NULL && i < 5)
    {
        i++;
        tokens[i] = strtok(NULL, " ");
    }
    return tokens;
}
