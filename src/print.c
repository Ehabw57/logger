#include "logger.h"
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
		printf("print doesnt have any extra features now\n"); /*this line will be removed later*/

    if (employes_list == NULL)
    {
        printf("No employees in the list yet,\n add an employee or check [help add]!!\n");
        return 1;
    }

    while (employes_list != NULL)
    {
        printf("%d- %s\n", i, employes_list->name);
        employes_list = employes_list->next;
		i++;
    }
    return 0;
}

/**
 * print_log_entries - Prints log entries based on function arguments.
 * @args: Function arguments, not used in this implementation.
 * @state_ptr: Pointer to the logger state which holds the log entries list.
 * 
 * Return: 0 if print succeeded, 1 otherwise (e.g., if the list is empty).
 */
int print_log_entriys(char **args, void *state_ptr)
{
	logger_state_t* state = (logger_state_t*)state_ptr;
	log_entry_t *logs = state->log_entries;

	if (logs == NULL)
	{ 
		printf("No logs avalble yet!!\n");
		return(1);
	}
	if(*args != NULL)
		printf("print doesnt have any extra features now\n");/*this line will be removed later*/

    while (logs != NULL)
    {
        printf("Employee [%s] logged at %s", logs->employee, asctime(logs->log_time));
        logs = logs->next;
    }
	return (0);
}
/**
 * print_command - Handles the print command to display either logs or employees.
 * @args: Function arguments, where the first argument specifies what to print (e.g., "logs" or "employee").
 * @state_ptr: Pointer to the logger state which holds both employee and log entries lists.
 * 
 * Return: 0 if print succeeded, 1 otherwise (e.g., if the command is unrecognized).
 */
int print_command(char **args, void *state_ptr)
{
	if(args == NULL)
	{
		*args = "null";
here: 
		printf("print: Looks like [%s] is not a print feature\n\tcheck {help print}\n", args[0]);
		return (1);
	}

	if (string_compare(args[0], "logs") == 0)
		return(print_log_entriys(args+1, state_ptr));
	if (string_compare(args[0], "employee") == 0)
		return(print_employees(args+1, state_ptr));
	
	goto here;

}
