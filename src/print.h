#ifndef PRINT_H
#define PRINT_H
#include <sqlite3.h>

/* Print Functions */
int print(char **args, sqlite3 *db); /* Prints the contents of the database */
int help(char **args, sqlite3 *NotUsed); /* Displays the help manual */
#endif // PRINT_H
