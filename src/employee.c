#include "logger.h"
/**
 * add_employee_command - Adds a new employee to the employee list.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * 
 * Return: 0 on success, 1 on failure (e.g., employee already exists or memory allocation fails).
 */
int add_employee_command(char **args, void *state_ptr)
{
    logger_state_t *state = (logger_state_t *)state_ptr;
    employee_t *new_employee = NULL;
    if (args[0] == NULL)
    {
        return 1;
    }
    if (check_employee(args[0], state->employees) != NULL)
    {
        printf("Employee [%s] is already in the list\n", args[0]);
        return 1;
    }

    new_employee = malloc(sizeof(employee_t));
    if (new_employee == NULL)
    {
        return 1;
    }

    new_employee->name = strdup(args[0]);
    new_employee->next = state->employees;
    state->employees = new_employee;
    printf("Successfully added new employee [%s]\n", new_employee->name);
    return 0;
}
/**
 * check_employee - Checks if an employee exists in the employee list.
 * @employee_name: The name of the employee to search for.
 * @employee_list: The head of the employee list.
 * 
 * Return: Pointer to the employee's name if found, NULL otherwise.
 */
char *check_employee(char *employee_name, employee_t *employee_list)
{
    employee_t *current = employee_list;
    while (current != NULL)
    {
        if (string_compare(current->name, employee_name) == 0)
        {
            return current->name;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * remove_employee - Removes an employee from the employee list.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the employee list.
 * 
 * Return: 0 on success, 1 if the employee is not found or no name is provided.
 *
 */
 int remove_employee(char** args, void *state_ptr)
{
	logger_state_t *state = (logger_state_t *) state_ptr;
	employee_t *employee_list = state->employees;
	employee_t *tmp = NULL;
	char *employee_name = args[0];


	if (employee_name == NULL || check_employee(employee_name, employee_list) == NULL)
	{ 
		printf("Please provide a correct employee name to remove or type [help remove]\n");
		return(1);
	}

	while (employee_list != NULL)
	{
		employee_name = employee_list->name;
		if (string_compare(employee_name, args[0]) == 0)
		{
			if(employee_list == state->employees)
				state->employees = state->employees->next;
			else
				tmp->next = employee_list->next;
			printf("Good bye %s we are not going to miss you\n", employee_name);
			free(employee_list->name);
			free(employee_list);
			return (0);	
		}
		tmp = employee_list;
		employee_list = employee_list->next;
	}
	return(1);
}
