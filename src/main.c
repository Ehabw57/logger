#include "basic.h"
#include "db_essentials.h"
#include "input.h"
#include "string_utils.h"
#include "print.h"
#include "employee.h"
#include "logs.h"
#include "user.h"
#include <unistd.h>
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
	char *wellcome_string ="---------Welcome to the logger\nType 'help' for manual-----------\n"
		"\n**PLEASE NOTE**: You are currently on an IN-MEMORY database\n"
		"any changes or data you create will be lost on exit\n"
		"user (register) to create a user or (login) if you already have and account\n\n";

	printf("%s", wellcome_string);

	open_connection(NULL, &db);
	create_db(db);
	enable_foreign_key(db);
	
	while (1)
	{
		write(STDOUT_FILENO, COMMAND_PROMPT, 9);
		line = read_line(stdin); /*get line form stdin*/
		if(line == NULL)
			break;
		tokens = tokenize_line(line); /*toknize the line bases on space delimeter*/

		if (string_compare(tokens[0], "exit") == 0 )
			break;
		if (string_compare(tokens[0], "login") == 0 || string_compare(tokens[0], "register") == 0)
		{
			if(!string_compare(tokens[0], "login"))
				login(tokens + 1, &db);
			else
				register_user(stdin);
			free(line);
			free(tokens);
			continue;
		}

		for (i = 0; commands[i].func != NULL; i++) /*loop through the commands*/
		{
			if (string_compare(commands[i].name, tokens[0]) == 0) 
			{
				commands[i].func(tokens + 1, db); /*call the desired function*/
				break;
			}
		}
		if (commands[i].name == NULL && tokens[0])
			fprintf(stderr,"\nlogger: %s: command not avalible check [help]\n", tokens[0]);
		free(tokens);
		free(line);
	};
	exit_handler(db, &line, tokens);
}
