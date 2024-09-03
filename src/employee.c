#include "logger.h"

/**
 * add_employee_command - Adds a new employee to the employee list.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * Return: 0 on success, 1 if the employee is already in the list or no name is provided.
 */
int add_employee(char **args, sqlite3 *db)
{
	char *sql = NULL;
	int rc = 0;

	if (args == NULL || args[0] == NULL)
	{
		fprintf(stderr, "add: Please provide a correct employee name to add or type [help add]\n");
		return 1;
	}

	/* add the new employee to the database */
	sql = sqlite3_mprintf("INSERT INTO employees (name) VALUES ('%q');", args[0]);
	rc = sqlite3_exec(db, sql, 0, 0, 0);
	check_rc(rc, db, "add: Failed to add employee to the database");
	sqlite3_free(sql);

	rc = sqlite3_changes(db);
	if (rc == 0)
	{
		printf("add: Employee [%s] already exists\n", args[0]);
		return 1;
	}
	printf("Successfully added new employee [%s]\n",args[0]);
	return 0;
}

/**
 * remove_employee_command_db - Removes an employee from the employee list.
 * @args: Array of arguments, where the first element is the employee's name.
 * @db: The database connection.
 * Return: 0 on success, 1 if the employee is not found or no name is provided.
 */
int remove_employee(char **args, sqlite3 *db)
{
	char *sql = NULL;
	int rc = 0;

	if (args[0] == NULL)
	{
		printf("remove: Please provide a correct employee name or id to remove or type [help remove]\n");
		return 1;
	}
	else
	{
		if (string_compare(args[0], "name") == 0)
			sql = sqlite3_mprintf("DELETE FROM employees WHERE name = '%q';", args[1]);
		else if (string_compare(args[0], "id") == 0)
			sql = sqlite3_mprintf("DELETE FROM employees WHERE id = %d;", atoi(args[1]));
		else
		{
			printf("remove: Can't filter by [%s] attrbuite,  use [name || id] \n", args[0]);
			return(1);
		}
	}


	/* remove the employee from the database */
	rc = sqlite3_exec(db, sql, 0, 0, 0);
	check_rc(rc, db, "remove: Failed to remove employee from the database");
	sqlite3_free(sql);

	rc = sqlite3_changes(db);
	if (rc == 0)
	{
		printf("remove: There is no employee with %s = %s\n", args[0], args[1] ? args[1] : "null");
		return 1;
	}

	printf("Successfully removed employee [%s]\n", args[1]);
	return 0;
}
