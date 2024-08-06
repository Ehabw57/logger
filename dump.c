#include "logger.h"
#include <stdio.h>
#include <time.h>
/**
 *
 */

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
int dump_data(void *state_ptr)
{
	logger_state_t *state = (logger_state_t *) state_ptr;
	log_entry_t *logs = NULL;
	employee_t *employee_list = state->employees;
	FILE *dump_file = NULL;
	char date_buffer[20];

	if (state_ptr == NULL)
		return(1);

	dump_file = fopen("logs_data.log", "w");
	if (dump_file == NULL)
		return (1);

    while (state->log_entries != NULL)
    {
        logs = state->log_entries;
        strftime(date_buffer, sizeof(date_buffer), "%H:%M:%S-%d/%m/%Y", logs->log_time);
        fprintf(dump_file, "%s %s\n", logs->employee, date_buffer);
        free_log(state, logs);
    }
	fclose(dump_file);

	dump_file = fopen("employee_data.log", "w");
	if (dump_file == NULL)
		return (1);

	while(employee_list != NULL)
	{
		fprintf(dump_file, "%s\n", employee_list->name);
		remove_employee(&employee_list->name, state_ptr);
			employee_list = state->employees;
	}
	fclose(dump_file);
	return(0);
}

