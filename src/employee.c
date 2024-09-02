#include "logger.h"


/**
 * check_employee - Checks if an employee is in the employee list.
 * @employee_name: The name of the employee to check.
 * @employee_id: The id of the employee to check.
 * @employee_list: The list of employees to check.
 * Return: A pointer to the employee if found, NULL otherwise.
 */
employee_t *check_employee(char *employee_name, int employee_id, employee_t *employee_list)
{
    employee_t *current = employee_list;
    while (current != NULL)
    {
        if (string_compare(current->name, employee_name) == 0 || current->id == employee_id)
		{
			return current;
		}
        current = current->next;
    }
    return NULL;
}


/**
 * add_employee - Adds a new employee to the employee list.
 * @name: The name of the employee to add.
 * @id: The id of the employee to add.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * Return: 0 on success, 1 on failure (e.g., employee already exists or memory allocation fails).
 */
int add_employee(char *name, int id, void *state_ptr)
{
    logger_state_t *state = (logger_state_t *)state_ptr;
    employee_t *new_employee = NULL;

    if (name == NULL || id == 0)
        return 1;

    new_employee = malloc(sizeof(employee_t));
    if (new_employee == NULL)
        return 1;

    new_employee->name = strdup(name);
	new_employee->id =  id;
    new_employee->next = state->employees;
    state->employees = new_employee;
    return 0;
}

/**
 * remove_employee - Removes an employee from the employee list.
 * @name: The name of the employee to remove.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * Return: 0 on success, 1 if the employee is not found or no name is provided.
 */
 int remove_employee(employee_t *entry, void *state_ptr)
{
	logger_state_t *state = (logger_state_t *)state_ptr;
	employee_t **indirect = &(state->employees);

	if (entry == NULL || state == NULL)
		return 1;

	while (*indirect != entry)
		indirect = &(*indirect)->next;

	*indirect = entry->next;
	
	free(entry->name);
	free(entry);
	return 0;
}

/**
 * add_employee_command - Adds a new employee to the employee list.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * Return: 0 on success, 1 if the employee is already in the list or no name is provided.
 */
int add_employee_command(char **args, sqlite3 *db, void *state_ptr)
{
	logger_state_t *state = (logger_state_t *) state_ptr;
	char *sql = NULL;

	if (args == NULL || args[0] == NULL)
	{
		fprintf(stderr, "add: Please provide a correct employee name to add or type [help add]\n");
		return 1;
	}

	/* check if the employee is already in the database */
    if (check_employee(args[0], 0, state->employees) != NULL)
    {
        printf("add: Employee [%s] is already in the list\n", args[0]); 
        return 1;
    }

	/* add the new employee to the database and list */
	sql = sqlite3_mprintf("INSERT INTO employees (name) VALUES ('%q');", args[0]);
	if (sql_exec(sql, db, state, 0) != 0)
		return 1;

	sqlite3_free(sql);

	/* get and add the new employee to list */
	sql = sqlite3_mprintf("SELECT * FROM employees WHERE name = '%q';", args[0]);
	if (sql_exec(sql, db, state, callback_employees) != 0)
		return 1;

	sqlite3_free(sql);
	printf("Successfully added new employee [%s]\n",args[0]);
	return 0;
}

/**
 * remove_employee_command_db - Removes an employee from the employee list.
 * @args: Array of arguments, where the first element is the employee's name.
 * @db: The database connection.
 * Return: 0 on success, 1 if the employee is not found or no name is provided.
 */
int remove_employee_command(char **args, sqlite3 *db, void *state_ptr)
{
	logger_state_t *state = (logger_state_t *) state_ptr;
	employee_t *employee_list = state->employees;
	char *sql = NULL;
	employee_t *entry = NULL;

	if (args[0] == NULL)
		return 1;
	else
	{
		if (string_compare(args[0], "name") == 0)
			entry = check_employee(args[1] ? args[1] : NULL, 0, employee_list);
		else if (string_compare(args[0], "id") == 0)
			entry = check_employee(NULL, args[1] ? atoi(args[1]) : 0, employee_list);
		else
		{
			printf("remove: Can't filter by [%s] attrbuite,  use <name || id> \n", args[0]);
			return(1);
		}
	}

	if (entry == NULL)
	{
		printf("remove: There is no employee with %s = %s\n", args[0], args[1] ? args[1] : "null");
		return 1;
	}


	/* remove the employee from the database */
	sql = sqlite3_mprintf("DELETE FROM employees WHERE name = '%q';", entry->name);
	if (sql_exec(sql, db, state, 0) != 0)
		return 1;

	sqlite3_free(sql);
	printf("Successfully removed employee [%s]\n", entry->name);

	/* remove the employee from the list */
	return remove_employee(entry, state);
}
