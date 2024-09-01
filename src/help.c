#include "logger.h"
/**
 * print_general_help - Prints the general help manual for the logger application.
 */
static void print_general_help(void)
{
    printf("--------- Logger Application Help ---------\n");
    printf("Available commands:\n");
    printf("  log <employee_name> <time>    - Log an entry for the specified employee with the current time.\n");
    printf("  print logs                    - Print all log entries.\n");
    printf("  print employee                - Print all employee names.\n");
    printf("  add <employee_name>           - Add a new employee to the list.\n");
    printf("  remove <employee_name>        - Remove an employee from the list.\n");
    printf("  exit                          - Exit the application.\n");
    printf("  help [command]                - Show this help message or help for a specific command.\n");
}

/**
 * print_command_help - Prints the help manual for a specific command.
 * @command: The command for which help is requested.
 */
static void print_command_help(char *command)
{
    if (string_compare(command, "log") == 0)
    {
        printf("Usage: log <employee_name> <time>\n");
        printf("Description: Logs an entry for the specified employee with the provided time.\n");
        printf("Example: log JohnDoe 14:30:00-08/08/2024\n");
    }
    else if (string_compare(command, "print") == 0)
    {
        printf("Usage: print <type>\n");
        printf("Description: Prints data based on the type specified.\n");
        printf("  logs     - Print all log entries.\n");
        printf("  employee - Print all employee names.\n");
        printf("Example: print logs\n");
    }
    else if (string_compare(command, "add") == 0)
    {
        printf("Usage: add <employee_name>\n");
        printf("Description: Adds a new employee to the list.\n");
        printf("Example: add JohnDoe\n");
    }
    else if (string_compare(command, "remove") == 0)
    {
        printf("Usage: remove <employee_name>\n");
        printf("Description: Removes an employee from the list.\n");
        printf("Example: remove JohnDoe\n");
    }
    else
    {
        printf("No help available for command: %s\n", command);
    }
}

/**
 * help_command - Displays the help manual or specific command help based on the arguments provided.
 * @args: The arguments for the help command.
 * @state_ptr: Pointer to the logger state holder (not used in this function).
 * 
 * Return: Alwayas return 0
 */
int help_command(char **args, sqlite3 *NotUsed, void *state_ptr)
{
	(void) NotUsed;
	(void) state_ptr;
    if (args == NULL || *args == NULL)
    {
        print_general_help();
        return 0;
    }

    print_command_help(args[0]);
    return 0;
}
