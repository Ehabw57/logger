#include "logger.h"

void exit_handler(char **line, char **tokens)
	
{
    free(*line);
    free(tokens);
    // Free any other allocated memory in the state if necessary
    exit(0);
}

char *read_line()
{
    char *line = malloc(sizeof(char) * BUFFER_SIZE);
    if (line == NULL)
    {
        exit(12);
    }

    ssize_t length = read(STDIN_FILENO, line, BUFFER_SIZE);
    if (length < 0)
    {
        free(line);
        exit(12);
    }

    line[length - 1] = '\0';  // Terminate the line
    return line;
}

char **tokenize_line(char *line)
{
    char **tokens = malloc(sizeof(char *) * 6);  // Dynamic allocation for tokens
    if (tokens == NULL)
    {
        exit(12);
    }

    tokens[0] = strtok(line, " ");
    int i = 0;
    while (tokens[i] != NULL && i < 5)
    {
        i++;
        tokens[i] = strtok(NULL, " ");
    }
    return tokens;
}

