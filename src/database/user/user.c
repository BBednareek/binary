#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user.h"
#include "database.h"

void listUsers(MYSQL *conn){
	if (mysql_query(conn, "SELECT id, username, role FROM users")){
		errorHandler(conn);
	}

	MYSQL_RES *res = mysql_store_result(conn);
	MYSQL_ROW row;

	printf("ID\tUsername\tRole\n");

	while ((row = mysql_fetch_row(res))){
		printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
	}
	mysql_free_result(res);
}

void deleteUser(MYSQL *conn){
	int user_id;

	printf("\nPodaj id uzytkownika, ktorego chcesz usunac: ");
	scanf("%d", &user_id);
	
	char query[256];
	snprintf(query, sizeof(query), "DELETE FROM users WHERE id = %d", user_id);
	if (mysql_query(conn, query)){
		errorHandler(conn);
	}
	
	system("clear");

	printf("Pomyslnie usunieto uzytkownika o id %d", user_id);
}


User* login(MYSQL *conn, const char *username, const char *password){
	static User loggedUser;

	const char *create_table_query = "CREATE TABLE if not exists users "
									"(id int AUTO_INCREMENT primary key not null, "
									"username varchar(50) not null unique, "
									"password varchar(50) not null, "
									"role varchar(10) not null)";

	if (mysql_query(conn,create_table_query)){
		errorHandler(conn);
	}

	char query[256];
	snprintf(query, sizeof(query),	"SELECT id, username, role "
									"FROM users WHERE username = '%s' AND password = '%s'", 
									username, password);

	if (mysql_query(conn, query)){
		errorHandler(conn);
		loggedUser.id = -1;
		return &loggedUser;
	}

	MYSQL_RES *res = mysql_store_result(conn);
	MYSQL_ROW row;

	if ((row = mysql_fetch_row(res))){
		loggedUser.id = atoi(row[0]);
		strncpy(loggedUser.username, row[1], sizeof(loggedUser.username) - 1);
		strncpy(loggedUser.role, row[2], sizeof(loggedUser.role) - 1);
		loggedUser.username[sizeof(loggedUser.username) - 1] = '\0';
		loggedUser.role[sizeof(loggedUser.role) - 1] = '\0';
		system("clear");
		printf("Pomyslnie zalogowano\n");
	} else {
		printf("Bledna nazwa uzytkownika lub haslo.\n");
		loggedUser.id = -1;
		return &loggedUser;
	}
	
	mysql_free_result(res);
	return &loggedUser;
}

void insertUser(MYSQL *conn, const char *username, const char *password, const char *role){
	char query[256];
	snprintf(query, sizeof(query), "INSERT INTO users (username, password, role) "
									"VALUES ('%s', '%s', '%s')",
									username, password, role);

	if (mysql_query(conn, query)){
		errorHandler(conn);
	}

	system("clear");
	printf("Pomyslnie dodano uzytkownika!");
}
