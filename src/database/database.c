#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

MYSQL* connectDatabase(){
	MYSQL *conn = mysql_init(NULL);

	if (conn == NULL){
		errorHandler(conn);
		return NULL;
	}

	if (mysql_real_connect(conn, "127.0.0.1", "root", "", "users_db", 3306, NULL, 0) == NULL){
		errorHandler(conn);
		return NULL;
	}

	return conn;
}

void errorHandler(MYSQL *conn){
	system("clear");
	
	printf("Blad podczas wykonania zapytania SQL!\n");
	printf("Tresc: %s\nKod bledu: %d", mysql_error(conn), mysql_errno(conn));
}

void closeDatabase(MYSQL *conn){
	mysql_close(conn);
}
