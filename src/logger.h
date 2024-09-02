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
	int id;
    int employee_id;
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
	int id;
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
	int (*func)(char **args, sqlite3 *, void *state_ptr);
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

/* Employee mangement fuction */
int add_employee(char *name, int id, void *state_ptr); /* Adds a new employee to the employee list */
int add_employee_command(char **args, sqlite3 *db, void *state_ptr); /* Adds a new employee to the database */
int remove_employee_command(char **args, sqlite3 *db, void *state_ptr); /* Removes an employee from the database */
int callback_employees(void *state_ptr, int argc, char **argv, char **azColName); /* Callback function for employee data */
int remove_employee(employee_t *entry, void *state_ptr); /* Removes an employee from the employee list */
employee_t *check_employee(char *employee_name, int employee_id, employee_t *employee_list) ; /* Checks if an employee is in the list */
/* Log Management Functions */
int log_command(char **args, sqlite3 *db, void *state_ptr); /* Starts a new log entry for an employee */
int unlog_command(char **args, sqlite3 *db, void *state_ptr); /* Removes a log entry from the database */

/* Input and Output Functions */
char *read_line(FILE *stream); /* Reads a line from standard input */
char **tokenize_line(char *line); /* Tokenizes a line based on space delimiters */
int print_command(char **args, sqlite3 *NotUsed, void *state_ptr); /* Prints data based on the type specified */
int help_command(char **args, sqlite3 *NotUsed, void *state_ptr); /* Displays help information */
char *strdup(const char *str); /* Duplicates a string */
int string_compare(char *s1, char *s2); /* Compares two strings */
void exit_handler(sqlite3 *db, char **line, char **tokens, void *state_ptr); /* Handles cleanup and exits the program */
/* Database Functions */
int create_db(sqlite3 *db); /* Creates the database tables */
int open_connection(char *db_name, sqlite3 **db); /* Opens a connection to the database */
int close_connection(sqlite3 *db); /* Closes the connection to the database */
int storage_reload(sqlite3 *db, logger_state_t *state); /* Reloads employee data from the database */
int sql_exec(char *sql, sqlite3 *db, logger_state_t *state_ptr, int (*callback)(void *, int, char **, char **)); /* Executes an SQL statement */



#endif /* LOGGER_H */
