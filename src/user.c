#include "user.h"
#include "input.h"
#include "db_essentials.h"
#include "string_utils.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <sys/stat.h>

char *users_table = "CREATE TABLE IF NOT EXISTS users("
			"id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"username TEXT NOT NULL UNIQUE,"
			"password TEXT NOT NULL,"
			"database TEXT NOT NULL UNIQUE);";
/**
 * random_ascii_char - generates a random ascii character between A-Z, a-z, 0-9
 * Return: random ascii character
 */
unsigned int random_ascii_char(void)
{
	int ranges[3][2] = {{65, 90}, {97, 122}, {48, 57}};
	int selected_range = rand() %3;
	int min = ranges[selected_range][0];
	int max = ranges[selected_range][1];

	return min + (rand() % (max -min +1));
}

/**
 * random_name - generates a random name of length between 6 and 24 characters
 * Note: the caller is responsible for freeing the memory allocated for the name
 * @name: pointer to store the generated name
 * Return: 0 on success, 1 on failure
 */
int random_name(char **name)
{
	unsigned int i = 0;
	unsigned int length = 6 + (rand() % (6 - 24));

	*name = malloc(sizeof(char) * (length +1));
	if (*name == NULL)
		return 1;

	for (i = 0; i < length; i++)
		(*name)[i] = (char)random_ascii_char();
	(*name)[length] = '\0';
	return 0;
}

/**
 * get_passwd - reads a password from the stream without echoing it
 * Note: the caller is responsible for freeing the memory allocated for the password
 * @stream: stream to read the password from
 * Return: password on success, NULL on failure
 */
char *get_passwd(FILE *stream)
{
    struct termios old, new;
	char *passwd = NULL;

    /* Turn echoing off and fail if we can't. */
    if (tcgetattr (fileno (stream), &old) != 0)
        return NULL;
    new = old;
    new.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stream), TCSAFLUSH, &new) != 0)
        return NULL;

    /* Read the password. */
    passwd = read_line(stream);
	if (passwd == NULL)
	{
		(void) tcsetattr (fileno (stream), TCSAFLUSH, &old);
		return NULL;
	}

    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old);

    return passwd;
}


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
int login(sqlite3 **user_db, FILE *stream)
{
	sqlite3 *db = NULL;
	char user_db_path[30];
	char *name = NULL;
	char *pass = NULL;
	char *sql = NULL;
	char **table = NULL;
	int row = 0;
	int rc = 0;

	rc = open_connection(DATABASE_PATH, &db);
	if(rc != SQLITE_OK)
	{
		close_connection(db);
		mkdir(DATABASE_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		open_connection(DATABASE_PATH, &db);
		sqlite3_exec(db, users_table, 0, 0, 0);
	}
	printf("username: ");
	name = read_line(stream);
	if (name == NULL) /*stream reached EOF*/
	{
		close_connection(db);
		return 1;
	}
	printf("password: ");
	pass = get_passwd(stream);
	if (pass == NULL) /*stream reached EOF*/
	{
		free(name);
		close_connection(db);
		return 1;
	}

	sql = sqlite3_mprintf("SELECT database FROM users WHERE username = '%q' AND password = '%q'", name, crypt(pass, "$1$"));
	
	rc = sqlite3_get_table(db, sql, &table, &row, NULL, NULL);
	if(check_rc(rc, db, "login: Faild to login") != 0)
	{
		free(name);
		free(pass);
		sqlite3_free(sql);
		close_connection(db);
		return 1;
	}
	if (row == 0)
	{
		fprintf(stderr, "\nlogin: username or passowrd error\n");
		free(name);
		free(pass);
		sqlite3_free(sql);
		sqlite3_free_table(table);
		close_connection(db);
		return 1;
	}
	printf("\nWellcome %s you have logined sucssfully\n", name);
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
	free(name);
	sqlite3_free_table(table);
	sqlite3_free(sql);
	free(pass);
	close_connection(db);
	return(0);

}
