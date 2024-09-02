#include "logger.h"
int print_headers = 0;
int print_data = 0;
/**
 * print_employees - Prints all employees in the employee list.
 * @args: Function arguments, not used in this implementation.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * 
 * Return: 0 if print succeeded, 1 otherwise (e.g., if the list is empty).
 */
int print_employees(char **args, void* state_ptr)
{
	logger_state_t *state = (logger_state_t *) state_ptr;
	employee_t *employes_list = state->employees;
	int i = 1;

	if(*args != NULL)
		printf("logger: Please note that print doesnt have any extra features now\n");/*this line will be removed later*/

    if (employes_list == NULL)
    {
        printf("logger: No employees in the list yet,\n add an employee or check [help add]!!\n");
        return 1;
    }

	printf("Employee_id 		Name\n");
    while (employes_list != NULL)
    {
        printf("%d			%s\n", employes_list->id, employes_list->name);
        employes_list = employes_list->next;
		i++;
    }
    return 0;
}
/**
 * callback_logs - Callback function to print logs.
 * @NotUsed: Not used.
 * @argc: Number of columns in the result.
 * @argv: Array of strings representing the result.
 * @azColName: Array of strings representing the column names.
 * Return: 0 if successful, 1 otherwise.
 */
int callback_logs(void *NotUsed, int argc, char **argv, char **azColName)
{
	(void) NotUsed;
	int i;
	int col_width = 15;

	/* print headers */
	if (!print_headers) {
		for (i = 0; i < argc; i++) {
			printf("| %-*s ", col_width, azColName[i]);
		}
		printf("\n");

		print_headers = 1;
	}

	/* print values */
	for (i = 0; i < argc; i++) {
		printf("| %-*s ", col_width, argv[i] ? argv[i] : "NULL");
	}
	printf("|\n");
	print_data = 1;

	return 0;;
}

int print_logs(sqlite3 *db, char**args)
{
	char *sql = sqlite3_mprintf("SELECT logs.id, employees.name, logs.log_time FROM logs JOIN employees ON logs.employee_id = employees.id");

	if (args[0] != NULL)
	{
		sqlite3_free(sql);
		sql = sqlite3_mprintf("SELECT logs.id, employees.name, logs.log_time FROM logs JOIN employees ON logs.employee_id = employees.id WHERE employees.name LIKE '%q'", args[0]);
	}
	if (sql_exec(sql, db, 0, callback_logs) != SQLITE_OK || !print_data)
	{
		printf("logger: No data found\n");
		return 1;
	}

	print_data = print_headers = 0; /*reset print flags*/
	sqlite3_free(sql);
	return (0);
}


/**
 * print_command - Handles the print command to display either logs or employees.
 * @args: Function arguments, where the first argument specifies what to print (e.g., "logs" or "employee").
 * @state_ptr: Pointer to the logger state which holds both employee and log entries lists.
 * 
 * Return: 0 if print succeeded, 1 otherwise (e.g., if the command is unrecognized).
 */
int print_command(char **args, sqlite3 *db, void *state_ptr)
{
	if(args == NULL)
	{
		*args = "empty_args";
		here: 
		printf("print: Looks like [%s] is not a print feature\n\tcheck {help print}\n", args[0]);
		return (1);
	}
	if (string_compare(args[0], "employee") == 0)
		return(print_employees(args+1, state_ptr));

	if (string_compare(args[0], "logs") == 0)
		return(print_logs(db, args+1));
	
	goto here;

}
