#include "logger.h"
/**
 * insert_log - Insert a new log entry into the database.
 * @db: The database connection
 * @employee_id: The ID of the employee
 * @local_time: The local time of the log entry
 * @state: The logger state
 * Return: 0 on success, 1 on failure
 */
int insert_log(sqlite3 *db, int employee_id, time_struct *local_time, logger_state_t *state)
{
	char *sql = NULL;
	char *time_str = NULL;

	if (local_time == NULL)
		return 1;

	time_str = asctime(local_time);
	time_str[strlen(time_str) - 1] = '\0';

	sql = sqlite3_mprintf("INSERT INTO logs (employee_id, log_time) VALUES (%d, '%q');", employee_id, time_str);
	if (sql_exec(sql, db, state, 0) != 0)
		return 1;

	sqlite3_free(sql);
	return 0;
}

/**
 * remove_log - Remove all log entries for a given employee.
 * @db: The database connection
 * @employee_id: The ID of the employee
 * @state: The logger state
 * Return: 0 on success, 1 on failure
 */
int remove_log(sqlite3 *db, int employee_id, logger_state_t *state)
{
	char *sql = NULL;

	sql = sqlite3_mprintf("DELETE FROM logs WHERE employee_id = %d;", employee_id);
	if (sql_exec(sql, db, state, 0) != 0)
		return 1;

	sqlite3_free(sql);
	return 0;
}
/**
 * log_command - Starts a new log entry for an employee.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the log entries and employee list.
 * 
 * Return: 0 on success, 1 on failure (e.g., employee not found, invalid input).
 */
int log_command(char **args, sqlite3 *db, void *state_ptr)
{
	logger_state_t *state = (logger_state_t *)state_ptr;
    time_t current_time = time(NULL);
	time_struct *local_time = NULL;
	employee_t *employee = NULL;
	employee_t *employee_list = state->employees;

	if (args == NULL || args[0] == NULL)
		return 1;

	employee = check_employee(NULL, atoi(args[0]), employee_list);
	if (employee == NULL)
	{
		printf("Could not find [%s] in the employee list\n", args[0]);
		return 1;
	}

    local_time = localtime(&current_time);
	return(insert_log(db, employee->id, local_time, state_ptr));
}
