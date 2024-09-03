#ifndef LOGGER_H
#define LOGGER_H

/* Define some constants */
#define BUFFER_SIZE 1024
#define COMMAND_PROMPT  "logger>> " 

/* Includeing some libs */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>
#include <ctype.h>

typedef struct tm time_struct;

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


/* Employee mangement fuction */
int remove_employee(char **args, sqlite3 *db); /* Removes an employee from the employee list */
int add_employee(char **args, sqlite3 *db); /* Adds a new employee to the employee list */

/* Log Management Functions */
int add_log(char **args, sqlite3 *db); /* Starts a new log entry for an employee */
int remove_log(char **args, sqlite3 *db); /* Removes a log entry from the database */

/* Print Functions */
int print(char **args, sqlite3 *db); /* Prints data */
int help(char **args, sqlite3 *NotUsed); /* Displays the help manual */

/* Input and Output Functions */
char *read_line(FILE *stream); /* Reads a line from standard input */
char **tokenize_line(char *line); /* Tokenizes a line based on space delimiters */
char *strdup(const char *str); /* Duplicates a string */
int string_compare(char *s1, char *s2); /* Compares two strings */
void exit_handler(sqlite3 *db, char **line, char **tokens); /* Handles program exit status */

/* Database Functions */
int create_db(sqlite3 *db); /* Creates the database tables */
int open_connection(char *db_name, sqlite3 **db); /* Opens a connection to the database */
int close_connection(sqlite3 *db); /* Closes the connection to the database */
int storage_reload(sqlite3 *db, void **head); /* Reloads the employees from the database */
int check_rc(int rc, sqlite3 *db, const char *msg); /* Checks the return code of a SQLite function */



#endif /* LOGGER_H */
