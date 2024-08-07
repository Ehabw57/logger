#include "logger.h"
/**
 *
 */

int dump_data(void *state_ptr)
{
	logger_state_t *state = (logger_state_t *) state_ptr;
	log_entry_t *logs = NULL;
	employee_t *employee_list = state->employees;
	FILE *dump_file = NULL;
	char date_buffer[20];

	if (state_ptr == NULL)
		return(1);

	dump_file = fopen(LOG_DATA_FILE, "w");
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

	dump_file = fopen(EMPLOYEE_DATA_FILE, "w");
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

