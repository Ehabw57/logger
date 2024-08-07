#include "logger.h"
#include <stdio.h>
#include <time.h>

/**
 */
int load_data(void *state_ptr, char *file)
{
	FILE *stream = NULL;
	char *line = NULL;
	time_struct parsed_time = {0};
	char **tokens = NULL;
	
	if (file == NULL)
		return (1);

	stream = fopen(file, "r");
	if (stream == NULL)
		return (1);

	for(line = read_line(stream); line != NULL; line = read_line(stream))
	{
		tokens = tokenize_line(line);
		if (tokens[1] != NULL)
		{
			if (strptime(tokens[1], "%H:%M:%S-%d/%m/%Y", &parsed_time) != NULL)
				add_log_entry(tokens[0], &parsed_time, state_ptr);
		}
		else
			add_employee_command(tokens, state_ptr);
		free(line);
		free(tokens);
	}
	fclose(stream);
	return (0);
}
