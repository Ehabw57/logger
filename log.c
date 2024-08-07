#include "logger.h"

int add_log_entry(char *employee_name, time_struct *time, logger_state_t *state)
{
    log_entry_t *new_log = NULL;
    log_entry_t *current = state->log_entries;

    if (employee_name == NULL || time == NULL)
    {
        return 1;
    }

    new_log = malloc(sizeof(log_entry_t));
    if (new_log == NULL)
    {
        return 1;
    }

    new_log->employee = strdup(employee_name);
    new_log->log_time = malloc(sizeof(time_struct));
    if (new_log->log_time == NULL)
    {
        free(new_log->employee);
        free(new_log);
        return 1;
    }
    memcpy(new_log->log_time, time, sizeof(time_struct));
    new_log->next = NULL;

    if (state->log_entries == NULL)
    {
        state->log_entries = new_log;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_log;
    }
    return 0;
}

int log_command(char **args, void *state_ptr)
{
    logger_state_t *state = (logger_state_t *)state_ptr;
    char *employee_name = NULL;
    time_t current_time;
    employee_t *employers_list = state->employees;

    if (employers_list == NULL || args[0] == NULL)
    {
        return 1;
    }

    employee_name = check_employee(args[0], employers_list);

    if (employee_name != NULL)
    {
        current_time = time(NULL);
        time_struct *local_time = localtime(&current_time);
        return add_log_entry(employee_name, local_time, state);
    }
    printf("Could not find [%s] in the employee list\n", args[0]);
    return 1;
}


int free_log(logger_state_t *logs, log_entry_t *free_log)
{
    log_entry_t *tmp = NULL;

    if (logs == NULL)
        return 1;

    if (free_log == NULL)
    {
        free_log = logs->log_entries;
        if (logs->log_entries != NULL)
            logs->log_entries = logs->log_entries->next;
    }
    else
    {
        if (logs->log_entries == free_log)
        {
            logs->log_entries = free_log->next;
        }
        else
        {
            for (tmp = logs->log_entries; tmp != NULL && tmp->next != free_log; tmp = tmp->next);
            if (tmp == NULL)
                return 1; // free_log was not found in the list
            tmp->next = free_log->next;
        }
    }

    free(free_log->employee);
    free(free_log->log_time);
    free(free_log);

    return 0;
}
