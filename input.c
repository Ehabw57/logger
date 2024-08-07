#include "logger.h"
#include <stdio.h>

void exit_handler(char **line, char **tokens, void *state_ptr)
{
	dump_data(state_ptr);
	free(*line);
	free(tokens);
	exit(0);
}

char *read_line(FILE* stream)
{
	size_t size = BUFFER_SIZE;
	int nread;
    char *line = malloc(sizeof(char) * BUFFER_SIZE);

	if (line == NULL) 
		exit(EXIT_FAILURE);

	nread = getline(&line, &size, stream);
	if (nread == -1) 
	{
		free(line);
		if (feof(stream))
				return (NULL);
		exit(EXIT_FAILURE);
	}

	line[nread - 1] = '\0';
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

