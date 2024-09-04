#ifndef DB_ESSENTIALS_H
#define DB_ESSENTIALS_H
#include <sqlite3.h>

/* Database Functions */
int open_connection(char *db_name, sqlite3 **db); /* Opens a connection to the database */
int close_connection(sqlite3 *db); /* Closes the connection to the database */
int create_db(sqlite3 *db); /* Creates the database tables */
int enable_foreign_key(sqlite3 *db) /* Enables foreign key constraints */;
int check_rc(int rc, sqlite3 *db, const char *msg); /* Checks the return code of a SQLite exec function */
#endif // DB_ESSENTIALS_H
