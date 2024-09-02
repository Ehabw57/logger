#include "logger.h"
#include <stdio.h>
#include <stdlib.h>


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
	sqlite3 *db = NULL;
	char *db_name = "logger.db";
	int i = 0;
	char *line = NULL;
	char **tokens = NULL;
	logger_state_t state = {NULL, NULL};
	command_t commands[] = {
		{"print", print_command},
		{"add", add_employee_command},
		{"remove", remove_employee_command},
		{"log", log_command},
		{"help", help_command},
		{NULL, NULL}
	};

	printf("---------Welcome to the logger\nType 'help' for manual-----------\n");

	open_connection(db_name, &db);
	create_db(db);
	storage_reload(db, &state);
	
	while (1)
	{
		write(STDOUT_FILENO, COMMAND_LINE, 10); /*write promit to the stdout stream*/
		line = read_line(stdin); /*get line form stdin*/
		if (line == NULL)
		{
			if(feof(stdin))
				break;
			exit(EXIT_FAILURE);
		}
		tokens = tokenize_line(line); /*toknize the line bases on space delimeter*/

		if (string_compare(tokens[0], "exit") == 0 )
			break;

		for (i = 0; commands[i].func != NULL; i++) /*loop through the commands*/
		{
			if (string_compare(commands[i].name, tokens[0]) == 0) 
			{
				commands[i].func(tokens + 1, db, &state); /*call the desired function*/
				break;
			}
		}
		if (commands[i].name == NULL && tokens[0])
			fprintf(stdout,"%s: %s: command not avalible check [help]\n",
					"logger", tokens[0]);
		free(tokens);
		free(line);
	};
	exit_handler(db, &line, tokens, &state);
}
