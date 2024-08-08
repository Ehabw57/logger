#include "logger.h"
/**
 * load_data - Loads log and employee data from a file into the logger state.
 * @state_ptr: Pointer to the logger state containing log entries and employee list.
 * @file: Path to the file containing the data to be loaded.
 * 
 * Return: 0 if successful, 1 if an error occurred (e.g., file opening failure).
 */int load_data(void *state_ptr, char *file)
{
	FILE *stream = NULL;
	char *line = NULL;
	time_struct parsed_time = {0};
	char **tokens = NULL;
	
	if (file == NULL)
		return (1);

	/*open the file in the reading mode*/
	stream = fopen(file, "r");
	if (stream == NULL)
		return (1);

	/*load the data of the file*/
	for(line = read_line(stream); line != NULL; line = read_line(stream))
	{
		tokens = tokenize_line(line);
		
		/*if there is a second token that means it is a log data*/
		if (tokens[1] != NULL)
		{
			if (strptime(tokens[1], "%H:%M:%S-%d/%m/%Y", &parsed_time) != NULL)
				add_log_entry(tokens[0], &parsed_time, state_ptr);
		}
		/*else it means an employee data*/
		else
			add_employee_command(tokens, state_ptr);
		free(line);
		free(tokens);
	}
	fclose(stream);
	return (0);
}
