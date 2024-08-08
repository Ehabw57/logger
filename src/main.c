#include "logger.h"
#include <stdio.h>
#include <time.h>

/**
 * main - Entry point for the logger application.
 * 
 * This program serves as a logger application that allows users to log, print,
 * add, and remove employee data. It loads existing data from files, interprets
 * user commands, and executes corresponding functions. The program continues
 * running until the user inputs the "exit" command.
 * 
 * Return: 0 on program success, or 1 otherwise.
 */
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
		{"help", help_command},
		{NULL, NULL}
	};

	printf("---------Welcome to the logger\nType 'help' for manual-----------\n");

	load_data(&state, LOG_DATA_FILE); /*load program previous data*/
	while (1)
	{
		write(STDOUT_FILENO, COMMAND_LINE, 10); /*write promit to the stdout stream*/
		line = read_line(stdin); /*get line form stdin*/
		tokens = tokenize_line(line); /*toknize the line bases on space delimeter*/

		if (string_compare(tokens[0], "exit") == 0)
		{
			exit_handler(&line, tokens, &state); /*termnaite the program is first input is exit*/
		}

		for (i = 0; commands[i].function != NULL; i++) /*loop through the commands*/
		{
			if (string_compare(commands[i].name, tokens[0]) == 0) 
			{
				commands[i].function(tokens + 1, &state); /*call the desired function*/
				break;
			}
		}
		if (commands[i].name == NULL)
			fprintf(stdout,"%s: %s: command not avalible check [help]\n",
					"logger", tokens[0]);
		free(tokens);
		free(line);
	};
	exit_handler(&line, tokens, &state);
}
