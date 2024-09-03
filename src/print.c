#include "logger.h"

void print_table(char **table, int row, int column)
{
	int i  = 0;
	int col_width = 15;
	/* print column headrs */
	for (i = 0; i < column; i++)
		printf("| %-*s ", col_width, table[i]);
	
	/* print rows data */
	for (i = column; i < (row + 1) * column; i++)
	{
		if (i % column == 0)
			printf("\n");
		printf("| %-*s ", col_width, table[i]);
	}
	printf("\n");
	sqlite3_free_table(table);
}

int print_employees(sqlite3 *db, char **args)
{
	(void) args;
	char *sql = "SELECT * FROM employees";
	int rc = 0;
	char **table = NULL;
	int column, row = 0;

	rc = sqlite3_get_table(db, sql, &table, &row, &column, NULL);

	if (check_rc(rc, db, "print: Failed to get employees") != 0)
		return 1;

	if (row == 0)
	{
		printf("print: No employees found\n");
		return 1;
	}

	print_table(table, row, column);
	return 0;
}

int print_logs(sqlite3 *db, char **args)
{
	char *basic = "SELECT logs.id, employees.name, logs.log_time FROM logs JOIN employees ON logs.employee_id = employees.id";
	char *sql = NULL;
	int rc = 0;
	char **table = NULL;
	int column, row = 0;

	if (args[0] == NULL)
		sql = sqlite3_mprintf("%s", basic);
	else
	{
		if (string_compare(args[0], "name") == 0)
			sql = sqlite3_mprintf("%s WHERE employees.name LIKE '%q'", basic, args[1] ? args[1] : "");
		else if (string_compare(args[0], "id") == 0)
			sql = sqlite3_mprintf("%S WHERE employees.id = %q", basic, args[1] ? args[1] : "");
		else
		{
			printf("print: Can't filter by [%s] attrbuite,  use <name || id> \n", args[0]);
			return(1);
		}
	}
	rc = sqlite3_get_table(db, sql, &table, &row, &column, NULL);
	if (check_rc(rc, db, "print: Failed to get logs") != 0)
	{
		sqlite3_free(sql);
		return 1;
	}
	if (row == 0)
	{
		printf("print: No logs found %s %s\n", args[0] ? "for the provided filter" : "",
				args[0] ? args[1] : "");
		sqlite3_free(sql);
		return 1;
	}
	sqlite3_free(sql);
	print_table(table, row, column);
	return 0;
}

int print(char **args, sqlite3 *db)
{
	if(args == NULL)
	{
		*args = "null";
		here: 
		printf("print: [%s] is not a print feature, check {help print}\n", args[0]);
		return (1);
	}
	if (string_compare(args[0], "employee") == 0)
		return(print_employees(db, args+1));

	if (string_compare(args[0], "logs") == 0)
		return(print_logs(db, args+1));
	
	goto here;

}
