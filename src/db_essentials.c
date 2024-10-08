#include "db_essentials.h"
#include <stdio.h>
/**
 * check_rc - Check the return code of a sqlite3_exec function
 * And print custom error message
 * @rc: The return code
 * @db: The database connection
 * @msg: The message to print on error
 * Return: 0 on success, non-zero on failure
 */
int check_rc(int rc, sqlite3 *db, const char *msg)
{
	(void)db;
	(void)msg;
    if (rc != SQLITE_OK)
	{
        fprintf(stderr, "%s\n", msg);
		return 1;
    }
	return 0;
}
/**
 * open_connection - Open a connection to the database
 * @db_name: The name of the database
 * @db: A pointer to the database connection
 * Return: 0 on success, non-zero on failure
 */
int open_connection(char * db_name, sqlite3 **db) {
	int rc = sqlite3_open(db_name, db);
	return(check_rc(rc, *db, "logger: Can't open database file, (/data) dir have been deleted or corrupted\n\trestarting..."));
}

/**
 * close_connection - Close the connection to the database
 * @db: The database connection
 * Return: 0 on success, non-zero on failure
 */
int close_connection(sqlite3 *db) {
	int rc = sqlite3_close(db);
	return(check_rc(rc, db, "Can't close database"));
}

/**
 * create_db - Create the database tables
 * @db: The database connection
 * Return: 0 on success, non-zero on failure
 */
int create_db(sqlite3 *db) {
	char *sql = "CREATE TABLE IF NOT EXISTS employees ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"name TEXT NOT NULL UNIQUE);"
			"CREATE TABLE IF NOT EXISTS logs ("
			"id INTEGER PRIMARY KEY, "
			"employee_id INTEGER NOT NULL, "
			"log_time TEXT, "
			"FOREIGN KEY (employee_id) REFERENCES employees(id) ON DELETE CASCADE);";
	int rc = sqlite3_exec(db, sql, 0, 0, 0);
	return(check_rc(rc, db, "Failed to create table"));
}


/**
 * enable_foreign_key - Enable foreign key constraints
 * @db: The database connection
 * Return: 0 on success, non-zero on failure
 */
int enable_foreign_key(sqlite3 *db) 
{
	int rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
	return(check_rc(rc, db, "Failed to enable foreing_key"));
}
