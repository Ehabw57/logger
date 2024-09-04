#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <sqlite3.h>

/* Employee mangement fuction */
int remove_employee(char **args, sqlite3 *db); /* Removes an employee from the database */
int add_employee(char **args, sqlite3 *db); /* Adds a new employee to the database */

#endif // EMPLOYEE_H
