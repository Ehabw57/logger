#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <sqlite3.h>
	
#define DATABASE_PATH "data/logger.db"
#define DATABASE_DIR "data"
int login(sqlite3 **db, FILE *stream);
int register_user(FILE *stream);
#endif // USER_H
