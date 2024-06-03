#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user.h"
#include "database.h"
#include "ui.h"

int main(){
	MYSQL *conn = connectDatabase();

	char username[50];
	char password[50];

	User loggedUser;
	User* userPtr = &loggedUser;

	printf("Nazwa uzytkownika: ");
	scanf("%49s", username);
	printf("Haslo: ");
	scanf("%49s", password);

	userPtr = login(conn, username, password);
	
	if (userPtr->id == -1){
		errorHandler(conn);
	}

	if (strcmp(userPtr->role, "admin") == 0){
		adminMenu(conn);
	}
	
	userMenu(conn, userPtr);
	
	closeDatabase(conn);
	return 0;
}

