#include "logger.h"


int check_rc(int rc, sqlite3 *db, const char *msg)
{
    if (rc != SQLITE_OK)
	{
        fprintf(stderr, "%s: %s\n", msg, sqlite3_errmsg(db));
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
	return(check_rc(rc, *db, "Can't open database"));
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
			"employee_id INTEGER, "
			"log_time TEXT, "
			"FOREIGN KEY (employee_id) REFERENCES employees(id));";
	int rc = sqlite3_exec(db, sql, 0, 0, 0);
	return(check_rc(rc, db, "Failed to create table"));
}
