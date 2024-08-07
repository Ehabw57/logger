#ifndef LOGGER_H
#define LOGGER_H
#define _XOPEN_SOURCE 700 /* Enable GNU extensions for strptime*/

#define BUFFER_SIZE 1024
#define COMMAND_LINE "Logger>> "
#define LOG_DATA_FILE "./logs_data.log"
#define EMPLOYEE_DATA_FILE "./employee_data.log"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

typedef struct tm time_struct;

/**
 * Struct to contain log entries
 * @employee: The employee name
 * @log_time: Time of the log
 * @next: Pointer to the next log entry
 */
typedef struct log_entry
{
    char *employee;
    time_struct *log_time;
    struct log_entry *next;
} log_entry_t;

/**
 * Struct to hold employee names
 * @name: Name of the employee
 * @next: Pointer to the next employee
 */
typedef struct employee
{
    char *name;
    struct employee *next;
} employee_t;

/**
 * Struct command - holds the name of the command and its function
 * @name: Command name
 * @function: Function of the command
 */
typedef struct command
{
    char *name;
    int (*function)(char **, void *);
} command_t;

/**
 * Struct to hold the state of the logger application for both employee, log_entrys lists
 * @log_entries: Pointer to the first log entry
 * @employees: Pointer to the first employee
 */
typedef struct logger_state
{
    log_entry_t *log_entries;
    employee_t *employees;
} logger_state_t;

void exit_handler(char **line, char **tokens, void* state_ptr);
char *read_line(FILE *stream); /*get line for standerd input*/
char **tokenize_line(char *line); /*toknaize the line based on space delimters*/
int add_log_entry(char *employee_name, time_struct *time, logger_state_t *state); /*add a new employee log to the log entriyes*/
char *check_employee(char *employee_name, employee_t *employee_list); /*search for a spasific employee in the employee list*/
int log_command(char **args, void *state); /*start a new log*/
int print_command(char **args, void *state_ptr) ; /*start a new print*/
int add_employee_command(char **args, void *state); /*add a new employee to the list*/
char *strdup(const char *str); /*duplicate a string*/
int string_compare(char *s1, char *s2); /*compare 2 strings*/
int remove_employee(char** args, void *state_ptr);
int dump_data(void *state_ptr);
int free_log(logger_state_t *logs, log_entry_t *free_log);
int load_data(void *state_ptr, char *file);
#endif

