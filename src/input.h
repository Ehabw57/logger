#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include <sqlite3.h>

#define BUFFER_SIZE 1024
char *read_line(FILE *stream); /* Reads a line from standard input */
char **tokenize_line(char *line); /* Tokenizes a line based on space delimiters */
void exit_handler(sqlite3 *db, char **line, char **tokens); /* Handles program exit status */
#endif // INPUT_H
