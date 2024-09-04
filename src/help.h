#ifndef HELP_H
#define HELP_H
#include <sqlite3.h>

static void print_general_help(void); /* Print general help */
static void print_command_help(char *command); /* Print help for a specific command */
int help(char **args, sqlite3 *NotUsed) ; /* Help command */

#endif // HELP_H
