#ifndef LOGGER_H
#define LOGGER_H

#define _XOPEN_SOURCE 700 /* Enable GNU extensions for strptime */
#define BUFFER_SIZE 1024
#define COMMAND_LINE "Logger>> " /* Prompt for each command */
#define LOG_DATA_FILE "./data/logs_data.log" /* File for storing log data */

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

typedef struct tm time_struct;

/**
 * struct log_entry - Contains log entries.
 * @employee: The name of the employee associated with the log entry.
 * @log_time: The time the log entry was created.
 * @next: Pointer to the next log entry in the linked list.
 */
typedef struct log_entry
{
    char *employee;
    time_struct *log_time;
    struct log_entry *next;
} log_entry_t;

/**
 * struct employee - Holds employee information.
 * @name: The name of the employee.
 * @next: Pointer to the next employee in the linked list.
 */
typedef struct employee
{
    char *name;
    struct employee *next;
} employee_t;

/**
 * struct command - Holds the name of a command and its corresponding function.
 * @name: The name of the command.
 * @function: Pointer to the function that executes the command.
 */
typedef struct command
{
    char *name;
    int (*function)(char **, void *);
} command_t;

/**
 * struct logger_state - Holds the state of the logger, including employee and log data.
 * @log_entries: Pointer to the first log entry in the linked list.
 * @employees: Pointer to the first employee in the linked list.
 */
typedef struct logger_state
{
    log_entry_t *log_entries;
    employee_t *employees;
} logger_state_t;

/* Function Prototypes */
char *read_line(FILE *stream); /* Reads a line from standard input */
char **tokenize_line(char *line); /* Tokenizes a line based on space delimiters */
int log_command(char **args, void *state); /* Starts a new log entry */
int print_command(char **args, void *state_ptr); /* Prints log or employee data */
int add_employee_command(char **args, void *state); /* Adds a new employee to the list */
int help_command(char **args, void *state_ptr); /*help manual*/
int remove_employee(char **args, void *state_ptr); /* Removes an employee from the list */
char *check_employee(char *employee_name, employee_t *employee_list); /* Searches for a specific employee in the list */
int add_log_entry(char *employee_name, time_struct *time, logger_state_t *state); /* Adds a new log entry for an employee */
int remove_log_entry(logger_state_t *logger_state, log_entry_t *target_log) ; /* Frees a log entry */
int dump_data(void *state_ptr); /* Dumps all data to the data files */
int load_data(void *state_ptr, char *file); /* Loads all data from the data files */
char *strdup(const char *str); /* Duplicates a string */
int string_compare(char *s1, char *s2); /* Compares two strings */
void exit_handler(char **line, char **tokens, void *state_ptr); /* Handles exit cases, freeing resources */
/* Database Functions */
int create_db(sqlite3 *db); /* Creates the database tables */
int open_connection(char *db_name, sqlite3 **db); /* Opens a connection to the database */
int close_connection(sqlite3 *db); /* Closes the connection to the database */


#endif /* LOGGER_H */
