#include "logger.h"

/**
 * open_connection - Open a connection to the database
 * @db_name: The name of the database
 * @db: A pointer to the database connection
 * Return: 0 on success, non-zero on failure
 */
int open_connection(char * db_name, sqlite3 **db) {
	int rc = sqlite3_open(db_name, db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
		return rc;
	}
	return 0;
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
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "employee_id INTEGER,"
                "log_time TEXT,"
                "FOREIGN KEY(employee_id) REFERENCES employees(id));";
    char *err_msg = NULL;
	int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return rc;
	}
	return 0;
}
/**
 * close_connection - Close the connection to the database
 * @db: The database connection
 * Return: 0 on success, non-zero on failure
 */
int close_connection(sqlite3 *db) {
	int rc = sqlite3_close(db);
	if (rc) {
		fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
		return rc;
	}
	return 0;
}
