#include "logger.h"

/**
 * callback_employees - callback function for sqlite3_exec
 * @state_ptr: the logger state
 * @argc: the number of columns in the result
 * @argv: the result
 * @azColName: the column names
 * Return: 0 on success, 1 on failure
 */
int callback_employees(void *state_ptr, int argc, char **argv, char **azColName)
{
	(void) azColName;
	logger_state_t *state = (logger_state_t *)state_ptr;

	if (argc != 2)
		return 1;

	/* add employee to the list of employee*/
	add_employee(argv[1], atoi(argv[0]), state); 
	return 0;
}

/**
 * Storage_reload - reload the employees from the database
 *@db: the database
 *@state: the logger state
 * Return: 0 on success, 1 on failure
 */
int storage_reload(sqlite3 *db, logger_state_t *state)
{
	char *sql = "SELECT * FROM employees";

	if (sql_exec(sql, db, state, callback_employees) != 0)
		return 1;

	return 0;
}
