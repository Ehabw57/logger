#include "logger.h"
/**
 * dump_data - Dumps all log entries and employee data to respective files.
 * @state_ptr: Pointer to the logger state which holds the log entries and employee list.
 * 
 * Return: 0 if the data was successfully dumped, 1 if there was an error (e.g., file open failure).
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

	/* Open data file for writing*/
	dump_file = fopen(LOG_DATA_FILE, "w");
	if (dump_file == NULL)
		return (1);

	/* Write employee names to data file*/
	while(employee_list != NULL)
	{
		fprintf(dump_file, "%s\n", employee_list->name);
		remove_employee(&employee_list->name, state_ptr);
		employee_list = state->employees;
	}

	/* Write log entries to data file*/
	while (state->log_entries != NULL)
	{
		logs = state->log_entries;
		strftime(date_buffer, sizeof(date_buffer), "%H:%M:%S-%d/%m/%Y", logs->log_time);
		fprintf(dump_file, "%s %s\n", logs->employee, date_buffer);
		/* Remove log entry after writing*/
		remove_log_entry(state, logs);
	}

	fclose(dump_file);
	return(0);
}

