#include "logger.h"


int main(void)
{
    int i = 0;
    char *line = NULL;
    char **tokens = NULL;
    logger_state_t state = {NULL, NULL};
    command_t commands[] = {
        {"log", log_command},
        {"print", print_command},
        {"print_employees", print_command},
        {"add", add_employee_command},
		{"remove", remove_employee},
        {NULL, NULL}
    };

    printf("---------Welcome to the logger\nType 'help' for manual-----------\n");
    while (1)
    {
        line = read_line();
        tokens = tokenize_line(line);

        if (string_compare(tokens[0], "exit") == 0)
        {
            exit_handler(&line, tokens);
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
    }
    return 0;
}

