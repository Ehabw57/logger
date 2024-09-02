#include "logger.h"
#include <stdio.h>
#include <unistd.h>

/**
 * exit_handler - Handel all program exit status
 * @line; Read line
 * @tokens: tokens of the line
 * @state_ptr: Holder of the loggr state
 */
void exit_handler(sqlite3 *db, char **line, char **tokens, void *state_ptr)
{
	logger_state_t	*state = (logger_state_t *)state_ptr;
	employee_t *employee_list = state->employees;
	employee_t *tmp = NULL;

	while (employee_list)
	{
		tmp = employee_list;
		employee_list = employee_list->next;
		free(tmp->name);
		free(tmp);
	}
	free(*line);
	free(tokens);
	close_connection(db);
	printf("---------Goodbye---------\n");
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
 * Tokenizes a given line into individual tokens separated by spaces.
 * @line; The input string to tokenize.
 * Return: A dynamically allocated array of strings (tokens).
 */
char **tokenize_line(char *line)
{
    int i = 0;
    char **tokens = malloc(sizeof(char *) * 4);  /* you have to Dynamic allocation for tokens*/

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
