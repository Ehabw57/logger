#include "user.h"
#include "input.h"
#include "db_essentials.h"
#include "string_utils.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

char *users_table = "CREATE TABLE IF NOT EXISTS users("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"username TEXT NOT NULL UNIQUE,"
			"password TEXT NOT NULL,"
			"database TEXT NOT NULL UNIQUE);";

/**
 * register_user - registers a new user
 * Note: the caller is responsible for freeing the memory allocated for the user
 * Return: 0 on success, 1 on failure
 */
int register_user(FILE *stream)
{
	sqlite3 *db = NULL;
	char *user = NULL;
	char *pass = NULL;
	char *db_name = NULL;
	int rc = 0;
	

	if (open_connection(DATABASE_PATH, &db) != SQLITE_OK)
	{
		close_connection(db);
		mkdir(DATABASE_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		open_connection(DATABASE_PATH, &db);
	}
	sqlite3_exec(db, users_table, 0, 0, 0);

	/* repeat until user enters valid username */
	while (1) 
	{
		printf("Enter username: ");
		user = read_line(stream);
		if (user == NULL) /* stream reached EOF */
		{
			close_connection(db);
			return 1;
		}
		if (strlen(user) > 12 || strlen(user) < 5 || !no_space(user))
		{
			printf("Username must be between 5 to 12 characters and contain no spaces\n");
			free(user);
			continue;
		}
		break;
	}

	/* repeat until user enters valid password */
	while (1)
	{
		printf("Enter password: ");
		pass = get_passwd(stream);
		if (pass == NULL) /* stream reached EOF */
		{
			close_connection(db);
			free(user);
			return 1;
		}
		if (!no_space(pass) || strlen(pass) < 8)
		{
			printf("\nPassword must be at least 8 characters and contain no spaces\n");
			free(pass);
			continue;
		}
		break;
	}

	/* insert user into database */
	srand(time(NULL));
	random_name(&db_name);
	char *sql = sqlite3_mprintf("INSERT INTO users (username, password, database) VALUES ('%q', '%q', '%q');", user, crypt(pass, "$1$"), db_name);
	rc = sqlite3_exec(db, sql, 0, 0, 0);
	if (check_rc(rc, db, "Failed to insert user"))
	{
		fprintf(stderr, "user (%s) already reigstered\n", user);
		sqlite3_free(sql);
		close_connection(db);
		free(user);
		free(pass);
		free(db_name);
		return 1;
	}
	sqlite3_free(sql);
	
	printf("\nlogger: You have been registered successfully use (login) to login\n");
	free(pass);
	free(db_name);
	free(user);
	close_connection(db);

	return 0;
}

/**
 * login - logs in a user
 * @user_db: pointer to store the user's database
 * @stream: stream to read the username and password from
 * Return: 0 on success, 1 on failure
 */
int login(char **args, sqlite3 **user_db)
{
	sqlite3 *db = NULL;
	char user_db_path[30];
	char *pass = NULL;
	char *sql = NULL;
	char **table = NULL;
	int row = 0;
	int rc = 0;

	if (args == NULL || args[0] == NULL)
	{
		fprintf(stderr, "login: missing username\n");
		return 1;
	}

	rc = open_connection(DATABASE_PATH, &db);
	if(rc != SQLITE_OK)
	{
		close_connection(db);
		mkdir(DATABASE_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		open_connection(DATABASE_PATH, &db);
		sqlite3_exec(db, users_table, 0, 0, 0);
	}
	printf("password: ");
	pass = get_passwd(stdin);
	if (pass == NULL) /*stream reached EOF*/
	{
		close_connection(db);
		return 1;
	}

	sql = sqlite3_mprintf("SELECT database FROM users WHERE username = '%q' AND password = '%q'", args[0], crypt(pass, "$1$"));
	
	rc = sqlite3_get_table(db, sql, &table, &row, NULL, NULL);
	if(check_rc(rc, db, "login: Faild to login") != 0)
	{
		free(pass);
		sqlite3_free(sql);
		close_connection(db);
		return 1;
	}
	if (row == 0)
	{
		fprintf(stderr, "\nlogin: username or passowrd error\n");
		free(pass);
		sqlite3_free(sql);
		sqlite3_free_table(table);
		close_connection(db);
		return 1;
	}

	printf("\nWellcome %s you have logined sucssfully\n", args[0]);
	close_connection(*user_db);
	sprintf(user_db_path, "data/%s",table[1]);
	rc = open_connection(user_db_path , user_db);

	if(rc != SQLITE_OK)
	{
		mkdir(DATABASE_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		close_connection(*user_db);
		open_connection(user_db_path , user_db);
	}
	create_db(*user_db);
	enable_foreign_key(*user_db);
	sqlite3_free_table(table);
	sqlite3_free(sql);
	free(pass);

	close_connection(db);
	return(0);

}
