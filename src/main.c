#include "logger.h"
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
	command_t commands[] = {
		{"print", print},
		{"add", add_employee},
		{"remove", remove_employee},
		{"log", add_log},
		{"unlog", remove_log},
		{"help", help},
		{NULL, NULL}
	};

	printf("---------Welcome to the logger\nType 'help' for manual-----------\n");

	open_connection(db_name, &db);
	create_db(db);
	enable_foreign_key(db);
	
	while (1)
	{
		write(STDOUT_FILENO, COMMAND_PROMPT, 9);
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
				commands[i].func(tokens + 1, db); /*call the desired function*/
				break;
			}
		}
		if (commands[i].name == NULL && tokens[0])
			fprintf(stderr,"logger: %s: command not avalible check [help]\n", tokens[0]);
		free(tokens);
		free(line);
	};
	exit_handler(db, &line, tokens);
}
