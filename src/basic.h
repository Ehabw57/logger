#ifndef LOGGER_H
#define LOGGER_H

/* Define some constants */
#define COMMAND_PROMPT  "logger>> " 

#include <sqlite3.h>

/**
 * struct command - Holds the name of a command and its corresponding function.
 * @name: The name of the command.
 * @function: Pointer to the function that executes the command.
 */
typedef struct command
{
    char *name;
	int (*func)(char **, sqlite3 *) ;
} command_t;

#endif /* LOGGER_H */
