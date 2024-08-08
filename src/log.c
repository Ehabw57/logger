#include "logger.h"
/**
 * add_log_entry - Adds a new log entry to the log list.
 * @employee_name: The name of the employee associated with the log entry.
 * @time: The time when the log entry was created.
 * @state: Pointer to the logger state which holds the log entries list.
 * 
 * Return: 0 on success, 1 on failure (e.g., memory allocation failure, invalid input).
 */
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
/**
 * log_command - Starts a new log entry for an employee.
 * @args: Array of arguments, where the first element is the employee's name.
 * @state_ptr: Pointer to the logger state which holds the log entries and employee list.
 * 
 * Return: 0 on success, 1 on failure (e.g., employee not found, invalid input).
 */
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

/**
 * remove_log_entry - Removes and frees a log entry from the log list.
 * @logger_state: Pointer to the logger state which holds the log entries list.
 * @target_log: Pointer to the specific log entry to be removed and freed.
 * 
 * Return: 0 on success, 1 on failure (e.g., if the log entry is not found).
 */
int remove_log_entry(logger_state_t *logger_state, log_entry_t *target_log)
{
    log_entry_t *current_log = NULL;

    if (logger_state == NULL)
        return 1;

    if (target_log == NULL)
    {
        target_log = logger_state->log_entries;
        if (logger_state->log_entries != NULL)
            logger_state->log_entries = logger_state->log_entries->next;
    }
    else
    {
        if (logger_state->log_entries == target_log)
        {
            logger_state->log_entries = target_log->next;
        }
        else
        {
            for (current_log = logger_state->log_entries; current_log != NULL && current_log->next != target_log; current_log = current_log->next);
            if (current_log == NULL)
                return 1; // target_log was not found in the list
            current_log->next = target_log->next;
        }
    }

    free(target_log->employee);
    free(target_log->log_time);
    free(target_log);

    return 0;
}
