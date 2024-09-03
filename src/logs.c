#include "logger.h"
/**
 * log_command - Starts a new log entry for an employee.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the log entries and employee list.
 * 
 * Return: 0 on success, 1 on failure (e.g., employee not found, invalid input).
 */
int add_log(char **args, sqlite3 *db)
{
    time_t current_time = time(NULL);
	time_struct *local_time = NULL;
	char *ascit_time = NULL;
	char *sql = NULL;
	int rc = 0;
 
	if (args[0] == NULL)
	{
		printf("log: Please provide an employee name or ID\n");
		return 1;
	}

    local_time = localtime(&current_time);
	ascit_time = asctime(local_time);
	ascit_time[strlen(ascit_time) - 1] = '\0';
	if (string_compare(args[0], "name") == 0)
		sql = sqlite3_mprintf("INSERT INTO logs (employee_id, log_time) VALUES ((SELECT id FROM employees WHERE name = '%q'), '%q');" , args[1] ? args[1] : "", ascit_time);
	else if (string_compare(args[0], "id") == 0)
		sql = sqlite3_mprintf("INSERT INTO logs (employee_id, log_time) VALUES (%d, '%q');" , args[1] ? atoi(args[1]) : 0, ascit_time);
	else
	{
		printf("log: Can't filter by [%s] attrbuite,  use <name || id> \n", args[0]);
		return(1);
	}

	rc = sqlite3_exec(db, sql, 0, 0, 0);
	if (check_rc(rc, db, 0) != 0)
	{
		sqlite3_free(sql);
		printf("log: Employee %s = %s not found\n", args[0], args[1] ? args[1] : "null");
		return 1;
	}


	printf("log: Successfully added log for employee %s %s\n", args[0], args[1]);
	sqlite3_free(sql);
	return 0;
}

/**
 * unlog_command - Removes a log entry from the database.
 * @args: Array of arguments, where the first element is the log ID.
 * @state_ptr: Pointer to the logger state which holds the log entries and employee list.
 * 
 * Return: 0 on success, 1 on failure (e.g., log not found, invalid input).
 */
int remove_log(char **args, sqlite3 *db)
{
	char *sql = NULL;
	char *errmsg = NULL;
	int rc = 0;

	if (args[0] == NULL)
	{
		printf("unlog: Please provide a log ID\n");
		return 1;
	}
	sql = sqlite3_mprintf("DELETE FROM logs WHERE id = %s;", atoi(args[0]));
	rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
	if (check_rc(rc, db, errmsg) != 0)
	{
		sqlite3_free(errmsg);
		sqlite3_free(sql);
		printf("unlog: There is no log with id = %s\n", args[0]);
		return 1;
	}
	sqlite3_free(sql);
	printf("unlog: Successfully removed log (%s)\n", args[0]);
	return 0;
}
