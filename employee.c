#include "logger.h"

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

char *check_employee(char *employee_name, employee_t *employee_list)
{
    employee_t *current = employee_list;
    while (current != NULL)
    {
        if (strcmp(current->name, employee_name) == 0)
        {
            return current->name;
        }
        current = current->next;
    }
    return NULL;
}

/**
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
		printf("Please provide an correct employee name to remove or type [help remove]\n");
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
			free(employee_list->name);
			free(employee_list);
			return (1);	
		}
		tmp = employee_list;
		employee_list = employee_list->next;
	}
	return(1);
}
