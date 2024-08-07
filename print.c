#include "logger.h"
/**
 * print_employees - print all employess in the list
 * @args: Funciton arguments
 * @state_ptr: prointer to the logger state holder
 * Return: 0 if print succeded or 1 otherwise
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
 * print_log_entriys - print log entriys based on some arguments
 * @args: Funciton arguments
 * @state_ptr: prointer to the logger state holder
 * Return: 0 if print succeded or 1 otherwise
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
 */
int print_command(char **args, void *state_ptr)
{
	if(args == NULL)
	{
		printf("could not understand what to print\ncheck {help print}");
		return (1);
	}

	if (string_compare(args[0], "logs") == 0)
		return(print_log_entriys(args+1, state_ptr));
	if (string_compare(args[0], "employee") == 0)
		return(print_employees(args+1, state_ptr));

	printf("could not understand what to print\n\tcheck {help print}\n");
	return(1);
}
