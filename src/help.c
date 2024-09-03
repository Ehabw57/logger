#include "logger.h"
/**
 * print_general_help - Prints the general help manual for the logger application.
 */
static void print_general_help(void)
{
    printf("--------- Logger Application Help ---------\n");
    printf("Available commands:\n");
    printf("  log [<employee_name>|<id>          - Log an entry for the specified employee with the current time.\n");
    printf("  unlog <log_id>                     - Remove a log entry from logs table.\n");
    printf("  print [logs|employee]              - Print data from the application memory.\n");
    printf("  add <employee_name>                - Add a new employee to the list.\n");
    printf("  remove [<employee_name>|<id>]      - Remove an employee from the list.\n");
    printf("  help [command]                     - Show this help message or help for a specific command.\n");
    printf("  exit                               - Exit the application.\n");
}

/**
 * print_command_help - Prints the help manual for a specific command.
 * @command: The command for which help is requested.
 */
static void print_command_help(char *command)
{
    if (string_compare(command, "log") == 0)
    {
        printf("Usage: log [<employee_name> | <employee_id>] \n");
        printf("Description: Logs an entry for the specified employee with the current time.\n");
        printf("Example: log name Ehab_Hegazy\n");
    }
    else if (string_compare(command, "print") == 0)
    {
        printf("Usage: print <type>\n");
        printf("Description: Prints data based on the type specified.\n");
        printf("  logs  [name|id] [<employee_name> | <employee_id>]   - Print all log entries.\n");
        printf("  employee                                            - Print all employee names.\n");
        printf("Example: print logs\n");
    }
    else if (string_compare(command, "add") == 0)
    {
        printf("Usage:  add <employee_name>\n");
        printf("Description:     Adds a new employee to the list.\n");
        printf("Example: add Ehab_Hegazy\n");
    }
    else if (string_compare(command, "remove") == 0)
    {
        printf("Usage: remove [name|id] [<employee_name>|<employee_id]\n");
        printf("Description: Removes an employee from the list.\n");
        printf("Example: remove name Ehab_Hegazy\n");
    }
    else if (string_compare(command, "unlog") == 0)
	{
		printf("Usage: unlog <log_id>\n");
		printf("Description: Removes a log entry from logs table.\n");
		printf("Example: unlog 1\n");
	}
    else if (string_compare(command, "help") == 0)
	{
		printf("Usage: help [command]\n");
		printf("Description: Show this help message or help for a specific command.\n");
		printf("Example: help log\n");
	}
    else if (string_compare(command, "exit") == 0)
	{
		printf("Usage: exit\n");
		printf("Description: Exit the application.\n");
	}
    else
    {
        printf("No help available for command: %s\n", command);
    }
}

/**
 * help_command - Displays the help manual or specific command help based on the arguments provided.
 * @args: The arguments for the help command.
 * Return: Alwayas return 0
 */
int help(char **args, sqlite3 *NotUsed)
{
	(void) NotUsed;
    if (args == NULL || *args == NULL)
    {
        print_general_help();
        return 0;
    }

    print_command_help(args[0]);
    return 0;
}
