#include "logger.h"
#include <unistd.h>


int main(void)
{
	int i = 0;
	char *line = NULL;
	char **tokens = NULL;
	logger_state_t state = {NULL, NULL};
	command_t commands[] = {
		{"log", log_command},
		{"print", print_command},
		{"add", add_employee_command},
		{"remove", remove_employee},
		{NULL, NULL}
	};

	printf("---------Welcome to the logger\nType 'help' for manual-----------\n");

	load_data(&state, EMPLOYEE_DATA_FILE);
	load_data(&state, LOG_DATA_FILE);
  while (1)
    {
		write(STDOUT_FILENO, COMMAND_LINE, 10);
        line = read_line(stdin);
        tokens = tokenize_line(line);

        if (string_compare(tokens[0], "exit") == 0)
        {
            exit_handler(&line, tokens, &state);
        }

        for (i = 0; commands[i].function != NULL; i++)
        {
            if (string_compare(commands[i].name, tokens[0]) == 0)
            {
                commands[i].function(tokens + 1, &state);
            }
        }

        free(tokens);
        free(line);
    };
  exit_handler(&line, tokens, &state);
}
