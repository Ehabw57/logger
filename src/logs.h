#ifndef LOGS_H
#define LOGS_H
#include <sqlite3.h>

typedef struct tm time_struct;

/* Log Management Functions */
int add_log(char **args, sqlite3 *db); /* Starts a new log entry for an employee */
int remove_log(char **args, sqlite3 *db); /* Removes a log entry from the database */
#endif // LOGS_H
